// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

/**
 * 
 */
class UTileType;
UCLASS()
class AZUL_API UTile : public UObject
{
	GENERATED_BODY()

public:

	UTileType* GetTileType() const;
	void SetTileType(UTileType* TileType);

private:
	UTileType* Type;
};
