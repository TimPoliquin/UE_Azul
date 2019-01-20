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
/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AAzulGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAzulGameMode();

protected:
	/* Properties */
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	uint32 NumPlayers = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	uint32 BoardRadius = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAzulFactory> FactoryBlueprint;
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
	const int32 NumTilesPerFactory = 4;
	TArray<UTileType*> TileTypes;
	TArray<UTile*> Bag;
	TArray<UTile*> Box;
	TArray<AAzulFactory*> Factories;
	int32 GetNumFactories() const;
	void CreateTileTypes();
	void CreateTileType(FName Name, UMaterialInstance* MaterialInstance);
	void CreateTiles();
	void CreateFactories();
};



