// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulGameMode.h"
#include "AzulPlayerController.h"
#include "AzulPawn.h"
#include "AzulTile.h"
#include "AzulFactory.h"
#include "Tile/AzulTileType.h"

AAzulGameMode::AAzulGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAzulPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAzulPlayerController::StaticClass();
}

void AAzulGameMode::CreateTiles()
{
	const uint32 NumTilesPerType = 20;
	for (AzulTileType::TileType TileType : AzulTileType::TileTypes())
	{
		for (uint32 TileNum = 0; TileNum < NumTilesPerType; TileNum++)
		{
			AAzulTile* Tile = GetWorld()->SpawnActor<AAzulTile>();
			Tile->SetTileType(TileType);
			Tile->DetachRootComponentFromParent();
			Box.Add(Tile);
		}
	}
}

void AAzulGameMode::CreateFactories()
{
	const uint32 NumFactories = 5 + 2 * (GetNumPlayers() - 2);
	for (uint32 FactoryNum = 0; FactoryNum < NumFactories; FactoryNum++)
	{
		AAzulFactory* Factory = GetWorld()->SpawnActor<AAzulFactory>();
		Factories.Add(Factory);
	}
}

void AAzulGameMode::StartPlay()
{
	Super::StartPlay();
	CreateTiles();
	CreateFactories();
}
