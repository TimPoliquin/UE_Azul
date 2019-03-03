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
	TArray<AAzulTile*> AllTiles;
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
	if (Tiles.Num() > 0)
	{
		AllTiles.Append(Tiles);
	}
	AllTiles.Append(TilesToAdd);
	while (AllTiles.Num() > 0 && Locations.Num() > 0)
	{
		// Create Tile
		AAzulTile* Tile = AllTiles.Pop();
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

TArray<AAzulTile*> AAzulFactory::PullSelectedTiles()
{
	TArray<AAzulTile*> RemainingTiles;
	for (AAzulTile* Tile : SelectedTiles)
	{
		Tiles.Remove(Tile);
		Tile->OnTileClick.RemoveDynamic(this, &AAzulFactory::OnTileClicked);
	}
	RemainingTiles.Append(Tiles);
	Tiles.Empty();
	OnFactorySendTilesToCenter.Broadcast(RemainingTiles);
	return SelectedTiles;
}

void AAzulFactory::OnTileClicked(AAzulTile* ClickedTile)
{
	if (!ClickedTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recieved a click event, but no tile was provided!"))
		return;
	}
	bool Highlight = !ClickedTile->GetIsSelected();
	if (Highlight)
	{
		SelectTiles(ClickedTile->GetTileType());
		OnFactorySelectionStarted.Broadcast(this);
	}
	else
	{
		ResetTileSelection();
		OnFactorySelectionCancelled.Broadcast(this);
	}
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
	SelectedTiles.Empty();
}

void AAzulFactory::SelectTiles(UTileType* TileType)
{
	for (AAzulTile* Tile : Tiles)
	{
		if (Tile->GetTileType() == TileType)
		{
			Tile->Select(true);
			SelectedTiles.Push(Tile);
		}
		else
		{
			Tile->Select(false);
		}
	}
}
