// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wall.generated.h"

class UTile;
class UTileType;
USTRUCT()
struct FWallTile
{
	GENERATED_USTRUCT_BODY()
	UTile* Tile = nullptr;
	UTileType* TileType = nullptr;
};

/**
 * 
 */
UCLASS()
class AZUL_API UWall : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(TArray<UTileType*> TileTypes);
	void AddTile(int32 LineNum, UTile* Tile);
	bool IsComplete() const;

private:
	TArray<TArray<FWallTile>> WallLines;
};
