// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AzulGameMode.generated.h"

class UTileType;
class UTile;
class UMaterialInstance;
class AAzulFactory;
class AAzulTile;
class AGameBoard;
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
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	uint32 NumPlayers = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AGameBoard> GameBoardBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAzulTile> TileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInstance* RedMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInstance* BlueMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInstance* BlackMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInstance* OrangeMaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UMaterialInstance* WhiteMaterialInstance;

	/* Blueprint Callable Functions*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	UFUNCTION(BlueprintCallable, Category = "Play")
	void StartRound();

private:
	TArray<UTileType*> TileTypes;
	TArray<UTile*> Bag;
	TArray<UTile*> Box;
	AGameBoard* GameBoard;
	void CreateTileTypes();
	void CreateTileType(FName Name, UMaterialInstance* MaterialInstance);
	void CreateTiles();
	void CreateGameBoard();
	void ShuffleBag();
};



