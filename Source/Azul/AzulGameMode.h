// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AzulGameMode.generated.h"

class UBag;
class UTileType;
class UTile;
class UMaterialInstance;
class AAzulFactory;
class AAzulTile;
class APlayerBoard;
/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AAzulGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAzulGameMode();
	void ReturnToBox(TArray<UTile*> TilesToReturn);
	TArray<UTileType*> GetTileTypes() const;


protected:
	/* Properties */
	UPROPERTY(EditDefaultsOnly, Category = "Players")
	uint32 NumPlayers = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Players")
	FVector PlayerBoardPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Players")
	TSubclassOf<APlayerBoard> PlayerBoardBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Factories")
	uint32 BoardRadius = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Factories")
	TSubclassOf<AAzulFactory> FactoryBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Factories")
	TSubclassOf<AAzulFactory> CenterFactoryBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	TSubclassOf<AAzulTile> TileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* RedMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* BlueMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* BlackMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* OrangeMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* WhiteMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	UMaterialInstance* OneTileMaterialInstance;

	/* Blueprint Callable Functions*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	UFUNCTION(BlueprintCallable, Category = "Play")
	void StartRound();

private:
	const int32 NumTilesPerFactory = 4;
	TArray<UTileType*> TileTypes;
	UBag* Bag;
	TArray<UTile*> Box;
	TArray<AAzulFactory*> Factories;
	AAzulFactory* Center;
	UTileType* OneTileType;
	UTile* OneTile;
	TArray<APlayerBoard*> PlayerBoards;
	int32 GetNumFactories() const;
	AAzulFactory* FactoryWithSelection;
	void CreateBag();
	void CreateTileTypes();
	UTileType* CreateTileType(FName Name, UMaterialInstance* MaterialInstance);
	void CreateTiles();
	void CreateFactories();
	void CreatePlayerBoards();

	UFUNCTION()
	void OnFactorySelectionStarted(AAzulFactory* Factory);
	UFUNCTION()
	void OnFactorySelectionCancelled(AAzulFactory* Factory);
	UFUNCTION()
	void OnFactorySendTilesToCenter(TArray<AAzulTile*> TilesToSendToCenter);
	UFUNCTION()
	void OnPlayerBoardRowSelected(APlayerBoard* PlayerBoard, int32 SelectedRow);
};



