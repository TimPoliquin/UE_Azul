// Fill out your copyright notice in the Description page of Project Settings.

#include "Wall.h"
#include "Tile.h"
#include "TileType.h"

void UWall::Initialize(TArray<UTileType*> TileTypes)
{
	for (int32 LineIdx = 0; LineIdx < 5; LineIdx++)
	{
		TArray<FWallTile> WallLine;
		for (int32 WallTileIdx = 0; WallTileIdx < TileTypes.Num(); WallTileIdx++)
		{
			int32 TypeIdx = (LineIdx + WallTileIdx) % TileTypes.Num();
			FWallTile WallTile;
			WallTile.Tile = nullptr;
			WallTile.TileType = TileTypes[TypeIdx];
			WallLine.Add(WallTile);
		}
		WallLines.Add(WallLine);
	}
}

void UWall::AddTile(int32 LineNum, UTile* Tile)
{
	if (LineNum <= WallLines.Num())
	{
		TArray<FWallTile> WallLine = WallLines[LineNum - 1];
		for (FWallTile WallTile : WallLine)
		{
			if (WallTile.TileType == Tile->GetTileType())
			{
				WallTile.Tile = Tile;
				break;
			}
		}
	}
}

bool UWall::IsComplete() const
{
	return false;
}