// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bag.generated.h"

class UTile;
class AAzulTile;
/**
 * 
 */
UCLASS()
class AZUL_API UBag : public UObject
{
	GENERATED_BODY()

public:
	TArray<AAzulTile*> Draw(int32 NumToDraw);
	void Return(TArray<UTile*> TilesToReturn);
	int32 GetNumTilesRemaining() const;
	virtual UWorld* GetWorld() const;
	void SetWorld(UWorld* World);
private:
	UWorld* World;
	TArray<UTile*> Tiles;
	void Shuffle();
};
