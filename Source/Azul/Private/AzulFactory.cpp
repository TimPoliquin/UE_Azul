// Fill out your copyright notice in the Description page of Project Settings.

#include "AzulFactory.h"
#include "Tile/AzulTileType.h"
#include "AzulTile.h"

// Sets default values
AAzulFactory::AAzulFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAzulFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAzulFactory::AddTiles(TArray<AAzulTile*> TilesToAdd)
{
	Tiles.Append(TilesToAdd);
}

TArray<AAzulTile*> AAzulFactory::PullTiles(AzulTileType::TileType TypeToPull)
{
	TArray<AAzulTile*> PulledTiles;
	TArray<AAzulTile*> RemainingTiles;
	for (AAzulTile* Tile : Tiles)
	{
		if (Tile->GetTileType() == TypeToPull)
		{
			PulledTiles.Add(Tile);
		}
		else
		{
			RemainingTiles.Add(Tile);
		}
	}
	Tiles.Empty();
	// TODO - Send the remaining tiles to the Center
	return PulledTiles;
}
