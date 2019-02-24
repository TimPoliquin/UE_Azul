// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "TileType.h"
#include "AzulTile.h"

UTileType* UTile::GetTileType() const
{
	return Type;
}

void UTile::Initialize(TSubclassOf<AAzulTile> Blueprint, UTileType* TileType)
{
	TileBlueprint = Blueprint;
	Type = TileType;
}

AAzulTile* UTile::GetActor()
{
	return Actor;
}

AAzulTile* UTile::CreateActor(UWorld* World)
{
	if (!TileBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tile blueprint set!"))
		return nullptr;
	}
	if (!Actor)
	{
		Actor = World->SpawnActor<AAzulTile>(TileBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
		Actor->SetTile(this);
	}
	return Actor;
}

void UTile::DestroyActor()
{
	if (Actor)
	{
		Actor->Destroy();
		Actor = nullptr;
	}
}