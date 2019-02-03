// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBoard.generated.h"

class UTile;
class UTileType;
class AAzulGameMode;
class UPatternLine;
class UWall;
UCLASS()
class AZUL_API APlayerBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBoard();

public:
	void Initialize(AAzulGameMode* GameMode);
	bool CanAddTilesToLine(int32 LineNum, UTileType* TileType);
	void AddTilesToLine(int32 LineNum, TArray<UTile*> Tiles);
	void AddTilesToFloor(TArray<UTile*> Tiles);
	void OnRoundEnd();
	bool IsWallComplete() const;

private:
	TArray<UPatternLine*> PatternLines;
	TArray<UTile*> FloorLine;
	UWall* Wall;
	AAzulGameMode* GameMode;

	void AddTileToWall(int32 LineNum, UTile* Tile);

};
