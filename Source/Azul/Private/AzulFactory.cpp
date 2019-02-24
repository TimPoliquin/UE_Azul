// Fill out your copyright notice in the Description page of Project Settings.

#include "AzulFactory.h"
#include "AzulTile.h"
#include "TileType.h"

// Sets default values
AAzulFactory::AAzulFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AAzulFactory::PopulateTiles(TArray<AAzulTile*> TilesToAdd)
{
	FVector FactoryOrigin;
	FVector FactoryExtent;
	FVector FactoryScale = GetActorScale();
	GetActorBounds(false, FactoryOrigin, FactoryExtent);
	float QuadrantWidth = FactoryExtent.X / 2.f;
	float QuadrantHeight = FactoryExtent.Y / 2.f;
	TArray<FVector> Locations;
	// Currently, a Factory only supports 4 tiles
	Locations.Add(FVector(-1 * QuadrantWidth, QuadrantHeight, FactoryExtent.Z));
	Locations.Add(FVector(QuadrantWidth, QuadrantHeight, FactoryExtent.Z));
	Locations.Add(FVector(-1 * QuadrantWidth, -1 * QuadrantHeight, FactoryExtent.Z));
	Locations.Add(FVector(QuadrantWidth, -1 * QuadrantHeight, FactoryExtent.Z));
	while (TilesToAdd.Num() > 0 && Locations.Num() > 0)
	{
		// Create Tile
		AAzulTile* Tile = TilesToAdd.Pop();
		Tile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		// Position Tile
		FVector TileOrigin;
		FVector TileExtent;
		GetActorBounds(false, TileOrigin, TileExtent);
		Tile->SetActorRelativeLocation(Locations.Pop());
		Tile->OnTileClick.AddUniqueDynamic(this, &AAzulFactory::OnTileClicked);
		Tiles.Add(Tile);
	}
}

TArray<AAzulTile*> AAzulFactory::PullTiles(UTileType* TypeToPull)
{
	TArray<AAzulTile*> PulledTiles;
	TArray<AAzulTile*> RemainingTiles;
	for (AAzulTile* Tile : Tiles)
	{
		if (Tile->GetTileType() == TypeToPull)
		{
			PulledTiles.Add(Tile);
			Tile->OnTileClick.RemoveDynamic(this, &AAzulFactory::OnTileClicked);
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

void AAzulFactory::OnTileClicked(AAzulTile* ClickedTile)
{
	if (!ClickedTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recieved a click event, but no tile was provided!"))
		return;
	}
	UTileType* TileType = ClickedTile->GetTileType();
	bool Highlight = !ClickedTile->GetIsSelected();
	for (AAzulTile* Tile : Tiles)
	{
		if (Tile->GetTileType() == TileType)
		{
			Tile->Select(Highlight);
		}
		else
		{
			Tile->Select(false);
		}
	}
	OnFactorySelectionStarted.Broadcast(this);
}

bool AAzulFactory::GetIsCenter() const
{
	return IsCenter;
}

void AAzulFactory::SetIsCenter(bool ToSet)
{
	IsCenter = ToSet;
}

void AAzulFactory::ResetTileSelection()
{
	for (AAzulTile* Tile : Tiles)
	{
		Tile->Select(false);
	}
}
