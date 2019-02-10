// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulGameMode.h"
#include "AzulPlayerController.h"
#include "AzulPawn.h"
#include "Tile.h"
#include "AzulFactory.h"
#include "PlayerBoard.h"
#include "TileType.h"
#include "GameBoard.h"
#include "UnrealMathUtility.h"


AAzulGameMode::AAzulGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAzulPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAzulPlayerController::StaticClass();
}

void AAzulGameMode::CreateTileTypes()
{
	CreateTileType(FName(TEXT("Blue")), BlueMaterialInstance);
	CreateTileType(FName(TEXT("Orange")), OrangeMaterialInstance);
	CreateTileType(FName(TEXT("Red")), RedMaterialInstance);
	CreateTileType(FName(TEXT("Black")), BlackMaterialInstance);
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

void AAzulGameMode::Initialize()
{
	CreateTileTypes();
	CreateTiles();
	CreateGameBoard();
	StartRound();
}

void AAzulGameMode::StartRound()
{
	int32 NumTilesToPull = GameBoard->GetNumFactories() * 4;
	if (Bag.Num() < NumTilesToPull)
	{
		Bag.Append(Box);
		Box.Empty();
		ShuffleBag();
	}
	GameBoard->PopulateFactories(Bag);
}

void AAzulGameMode::ShuffleBag()
{
	for (int32 Idx = Bag.Num() - 1; Idx > 0; Idx--)
	{
		int32 NewIdx = FMath::FloorToInt(FMath::SRand() * (Idx + 1)) % Bag.Num();
		UTile* Temp = Bag[Idx];
		Bag[Idx] = Bag[NewIdx];
		Bag[NewIdx] = Temp;
	}
}

void AAzulGameMode::ReturnToBox(TArray<UTile*> TilesToReturn)
{
	Box.Append(TilesToReturn);
}

TArray<UTileType*> AAzulGameMode::GetTileTypes() const
{
	return TileTypes;
}

void AAzulGameMode::CreateGameBoard()
{
	GameBoard = GetWorld()->SpawnActor<AGameBoard>(GameBoardBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
	GameBoard->Initialize(NumPlayers);
}