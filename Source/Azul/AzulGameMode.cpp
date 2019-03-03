// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulGameMode.h"
#include "AzulPlayerController.h"
#include "AzulPawn.h"
#include "Tile.h"
#include "AzulFactory.h"
#include "TileType.h"
#include "Bag.h"
#include "UnrealMathUtility.h"
#include "AzulTile.h"
#include "PlayerBoard.h"


AAzulGameMode::AAzulGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAzulPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAzulPlayerController::StaticClass();
}

void AAzulGameMode::CreateBag()
{
	Bag = NewObject<UBag>();
	Bag->SetWorld(GetWorld());
}

void AAzulGameMode::CreateTileTypes()
{
	// Create tile types that have multiple tiles
	TileTypes.Add(CreateTileType(FName(TEXT("Blue")), BlueMaterialInstance));
	TileTypes.Add(CreateTileType(FName(TEXT("Orange")), OrangeMaterialInstance));
	TileTypes.Add(CreateTileType(FName(TEXT("Red")), RedMaterialInstance));
	TileTypes.Add(CreateTileType(FName(TEXT("Black")), BlackMaterialInstance));
	TileTypes.Add(CreateTileType(FName(TEXT("White")), WhiteMaterialInstance));
	// Create the OneTileType
	OneTileType = CreateTileType(FName(TEXT("One")), OneTileMaterialInstance);
}

UTileType* AAzulGameMode::CreateTileType(FName Name, UMaterialInstance* MaterialInstance)
{
	UTileType* TileType = NewObject<UTileType>();
	TileType->Initialize(Name, MaterialInstance);
	return TileType;
}

void AAzulGameMode::CreateTiles()
{
	const uint32 NumTilesPerType = 20;
	for (UTileType* TileType : TileTypes)
	{
		for (uint32 TileNum = 0; TileNum < NumTilesPerType; TileNum++)
		{
			UTile* Tile = NewObject<UTile>();
			Tile->Initialize(TileBlueprint, TileType);
			Box.Add(Tile);
		}
	}
	OneTile = NewObject<UTile>();
	OneTile->Initialize(TileBlueprint, OneTileType);
}

int32 AAzulGameMode::GetNumFactories() const
{
	return 5 + 2 * (NumPlayers - 2);
}

void AAzulGameMode::CreateFactories()
{
	const uint32 NumFactories = GetNumFactories();
	for (uint32 FactoryNum = 0; FactoryNum < NumFactories; FactoryNum++)
	{
		float CurrentAngle = 2 * PI * FactoryNum / NumFactories;
		float X = BoardRadius * FMath::Cos(CurrentAngle);
		float Y = BoardRadius * FMath::Sin(CurrentAngle);
		FVector SpawnLocation(X, Y, 0);
		AAzulFactory* Factory = GetWorld()->SpawnActor<AAzulFactory>(FactoryBlueprint, SpawnLocation, FRotator::ZeroRotator);
		Factory->OnFactorySelectionStarted.AddUniqueDynamic(this, &AAzulGameMode::OnFactorySelectionStarted);
		Factory->OnFactorySelectionCancelled.AddUniqueDynamic(this, &AAzulGameMode::OnFactorySelectionCancelled);
		Factory->OnFactorySendTilesToCenter.AddUniqueDynamic(this, &AAzulGameMode::OnFactorySendTilesToCenter);
		Factories.Add(Factory);
	}
	Center = GetWorld()->SpawnActor<AAzulFactory>(CenterFactoryBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
	Center->SetIsCenter(true);
	Center->OnFactorySelectionStarted.AddUniqueDynamic(this, &AAzulGameMode::OnFactorySelectionStarted);
	Center->OnFactorySelectionCancelled.AddUniqueDynamic(this, &AAzulGameMode::OnFactorySelectionCancelled);
}

void AAzulGameMode::Initialize()
{
	CreateBag();
	CreateTileTypes();
	CreateTiles();
	CreateFactories();
	CreatePlayerBoards();
	StartRound();
}

void AAzulGameMode::StartRound()
{
	int32 NumTilesToPull = GetNumFactories() * 4;
	if (Bag->GetNumTilesRemaining() < NumTilesToPull)
	{
		Bag->Return(Box);
		Box.Empty();
	}
	TArray<UTile*> Tiles;
	for(int32 FactoryIdx = 0; FactoryIdx < Factories.Num(); FactoryIdx++)
	{
		TArray<AAzulTile*> TilesDrawn = Bag->Draw(NumTilesPerFactory);
		AAzulFactory* Factory = Factories[FactoryIdx];
		Factory->PopulateTiles(TilesDrawn);
		Tiles.Empty();
	}
	// Get/Create the OneTile actor and move it to the center
	if (!OneTile->GetActor())
	{
		OneTile->CreateActor(GetWorld());
	}
	TArray<AAzulTile*> OneTiles;
	OneTiles.Add(OneTile->GetActor());
	Center->PopulateTiles(OneTiles);
}

void AAzulGameMode::ReturnToBox(TArray<UTile*> TilesToReturn)
{
	Box.Append(TilesToReturn);
	for (UTile* Tile : TilesToReturn)
	{
		Tile->DestroyActor();
	}
}

TArray<UTileType*> AAzulGameMode::GetTileTypes() const
{
	return TileTypes;
}

void AAzulGameMode::OnFactorySelectionStarted(AAzulFactory* Factory)
{
	for (AAzulFactory* FactoryToReset : Factories)
	{
		if (FactoryToReset != Factory)
		{
			FactoryToReset->ResetTileSelection();
		}
	}
	if (Factory != Center)
	{
		Center->ResetTileSelection();
	}
	FactoryWithSelection = Factory;
}

void AAzulGameMode::OnFactorySelectionCancelled(AAzulFactory* Factory)
{
	if (Factory == FactoryWithSelection)
	{
		FactoryWithSelection = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Recieved selection cancelled for unselected factory"))
	}
}

void AAzulGameMode::OnFactorySendTilesToCenter(TArray<AAzulTile*> TilesToSendToCenter)
{
	Center->PopulateTiles(TilesToSendToCenter);
}

void AAzulGameMode::CreatePlayerBoards()
{
	APlayerBoard* PlayerBoard = GetWorld()->SpawnActor<APlayerBoard>(PlayerBoardBlueprint, PlayerBoardPosition, FRotator::ZeroRotator);
	PlayerBoard->OnPlayerBoardRowSelected.AddUniqueDynamic(this, &AAzulGameMode::OnPlayerBoardRowSelected);
	PlayerBoards.Push(PlayerBoard);
}

void AAzulGameMode::OnPlayerBoardRowSelected(APlayerBoard* PlayerBoard, int32 SelectedRow)
{
	if (!FactoryWithSelection)
	{
		UE_LOG(LogTemp, Warning, TEXT("No factory selected -- aborting row selection"))
		return;
	}
	TArray<AAzulTile*> PulledTiles = FactoryWithSelection->PullSelectedTiles();
	PlayerBoard->AddTilesToLine(SelectedRow, PulledTiles);
	FactoryWithSelection = nullptr;
}