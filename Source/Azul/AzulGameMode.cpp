// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulGameMode.h"
#include "AzulPlayerController.h"
#include "AzulPawn.h"
#include "Tile.h"
#include "AzulFactory.h"
#include "TileType.h"

AAzulGameMode::AAzulGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAzulPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAzulPlayerController::StaticClass();
}

void AAzulGameMode::CreateTileTypes()
{
	CreateTileType(FName(TEXT("Red")), RedMaterialInstance);
	CreateTileType(FName(TEXT("Black")), BlackMaterialInstance);
	CreateTileType(FName(TEXT("Orange")), OrangeMaterialInstance);
	CreateTileType(FName(TEXT("Blue")), BlueMaterialInstance);
	CreateTileType(FName(TEXT("White")), WhiteMaterialInstance);
}

void AAzulGameMode::CreateTileType(FName Name, UMaterialInstance* MaterialInstance)
{
	UTileType* TileType = NewObject<UTileType>();
	TileType->Initialize(Name, MaterialInstance);
	TileTypes.Add(TileType);
}

void AAzulGameMode::CreateTiles()
{
	const uint32 NumTilesPerType = 20;
	for (UTileType* TileType : TileTypes)
	{
		for (uint32 TileNum = 0; TileNum < NumTilesPerType; TileNum++)
		{
			UTile* Tile = NewObject<UTile>();
			Tile->SetTileType(TileType);
			Box.Add(Tile);
		}
	}
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
		UE_LOG(LogTemp, Warning, TEXT("Positioning Factory at: %f, %f for angle %f"), X, Y, CurrentAngle)
		FVector SpawnLocation(X, Y, 0);
		AAzulFactory* Factory = GetWorld()->SpawnActor<AAzulFactory>(FactoryBlueprint, SpawnLocation, FRotator::ZeroRotator);
		Factory->SetTileBlueprint(TileBlueprint);
		Factories.Add(Factory);
	}
}

void AAzulGameMode::Initialize()
{
	CreateTileTypes();
	CreateTiles();
	CreateFactories();
	StartRound();
}

void AAzulGameMode::StartRound()
{
	int32 NumTilesToPull = GetNumFactories() * 4;
	if (Bag.Num() < NumTilesToPull)
	{
		Bag.Append(Box);
		Box.Empty();
	}
	TArray<UTile*> Tiles;
	for(int32 FactoryIdx = 0; FactoryIdx < Factories.Num(); FactoryIdx++)
	{
		for (int32 TileIdx = 0; TileIdx < NumTilesPerFactory; TileIdx++)
		{
			Tiles.Add(Bag.Pop());
		}
		UE_LOG(LogTemp, Warning, TEXT("NumTilesPerFactory: %d, NumTiles: %d"), NumTilesPerFactory, Tiles.Num())
		AAzulFactory* Factory = Factories[FactoryIdx];
		Factory->PopulateTiles(Tiles);
		Tiles.Empty();
	}
}
