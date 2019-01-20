// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "TileType.h"

UTileType* UTile::GetTileType() const
{
	return Type;
}

void UTile::SetTileType(UTileType* TileType)
{
	Type = TileType;
}