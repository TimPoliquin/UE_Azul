// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBoard.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerBoardRowSelected, APlayerBoard*, PlayerBoard, int32, SelectedRow);

class UTile;
class UTileType;
class AAzulGameMode;
class UPatternLine;
class UWall;
class AAzulTile;

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
	void AddTilesToLine(int32 LineNum, TArray<AAzulTile*> Tiles);
	void AddTilesToFloor(TArray<AAzulTile*> Tiles);
	void OnRoundEnd();
	bool IsWallComplete() const;

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void HandleRowClicked(int32 RowNum);

	FPlayerBoardRowSelected OnPlayerBoardRowSelected;

private:
	TArray<UPatternLine*> PatternLines;
	TArray<UTile*> FloorLine;
	UWall* Wall;
	AAzulGameMode* GameMode;

	void AddTileToWall(int32 LineNum, UTile* Tile);

};
