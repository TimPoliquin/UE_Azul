// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AzulGameMode.generated.h"

class AAzulFactory;
class AAzulTile;
/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AAzulGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAzulGameMode();
	virtual void StartPlay() override;
private:
	TArray<AAzulTile*> Bag;
	TArray<AAzulTile*> Box;
	TArray<AAzulFactory*> Factories;
	void CreateTiles();
	void CreateFactories();
};



