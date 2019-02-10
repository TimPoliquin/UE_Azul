// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBoard.h"
#include "PlayerBoard.h"
#include "AzulFactory.h"
#include "Tile.h"

// Sets default values
AGameBoard::AGameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameBoard::Initialize(int32 NumPlayers)
{
	CreatePlayerBoards(NumPlayers);
	CreateFactories(NumPlayers);
}

void AGameBoard::CreatePlayerBoards(int32 NumPlayers)
{
	FVector SpawnLocation;
	GetWorld()->SpawnActor<APlayerBoard>(PlayerBoardBlueprint, SpawnLocation, FRotator::ZeroRotator);
}


void AGameBoard::CreateFactories(int32 NumPlayers)
{
	const uint32 NumFactories = GetNumFactories(NumPlayers);
	for (uint32 FactoryNum = 0; FactoryNum < NumFactories; FactoryNum++)
	{
		float CurrentAngle = 2 * PI * FactoryNum / NumFactories;
		float X = BoardRadius * FMath::Cos(CurrentAngle);
		float Y = BoardRadius * FMath::Sin(CurrentAngle);
		FVector SpawnLocation(X, Y, 0);
		AAzulFactory* Factory = GetWorld()->SpawnActor<AAzulFactory>(FactoryBlueprint, SpawnLocation, FRotator::ZeroRotator);
		Factory->SetTileBlueprint(TileBlueprint);
		Factories.Add(Factory);
	}
}


int32 AGameBoard::GetNumFactories(int32 NumPlayers) const
{
	return 5 + 2 * (NumPlayers - 2);
}

void AGameBoard::PopulateFactories(TArray<UTile*> Bag)
{
	TArray<UTile*> Tiles;
	for (int32 FactoryIdx = 0; FactoryIdx < Factories.Num(); FactoryIdx++)
	{
		for (int32 TileIdx = 0; TileIdx < NumTilesPerFactory; TileIdx++)
		{
			Tiles.Add(Bag.Pop());
		}
		AAzulFactory* Factory = Factories[FactoryIdx];
		Factory->PopulateTiles(Tiles);
		Tiles.Empty();
	}
}
