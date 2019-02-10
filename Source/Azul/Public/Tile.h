// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

/**
 * 
 */
class AAzulTile;
class UTileType;
class UWorld;
UCLASS()
class AZUL_API UTile : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(TSubclassOf<AAzulTile> Blueprint, UTileType* TileType);
	UTileType* GetTileType() const;
	AAzulTile* CreateActor(UWorld* World);
	void DestroyActor();

private:
	TSubclassOf<AAzulTile> TileBlueprint;
	UTileType* Type;
	AAzulTile* Actor;
};
