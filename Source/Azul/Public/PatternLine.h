// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PatternLine.generated.h"

class UTile;
class UTileType;
class UWall;
class AAzulGameMode;
/**
 * 
 */
UCLASS()
class AZUL_API UPatternLine : public UObject
{
	GENERATED_BODY()

public:
	void SetSize(int32 SizeToSet);
	TArray<UTile*> AddTiles(TArray<UTile*> TilesToAdd);
	bool IsComplete() const;
	void OnRoundEnd(UWall* Wall, AAzulGameMode* GameMode);
	
private:
	int32 Size;
	TArray<UTile*> Tiles;
	UTileType* LineType;
};
