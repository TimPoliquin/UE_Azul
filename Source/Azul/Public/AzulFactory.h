// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AzulFactory.generated.h"

class UTileType;
class UTile;
class AAzulTile;
UCLASS()
class AZUL_API AAzulFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAzulFactory();

	void PopulateTiles(TArray<UTile*> TilesToAdd);
	TArray<AAzulTile*> PullTiles(UTileType* TypeToPull);
	void SetTileBlueprint(TSubclassOf<AAzulTile> TileBlueprintToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TSubclassOf<AAzulTile> TileBlueprint;
	TArray<AAzulTile*> Tiles;
};
