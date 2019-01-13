// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile/AzulTileType.h"
#include "AzulFactory.generated.h"

class AAzulTile;

UCLASS()
class AZUL_API AAzulFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAzulFactory();

	void AddTiles(TArray<AAzulTile*> TilesToAdd);
	TArray<AAzulTile*> PullTiles(AzulTileType::TileType TypeToPull);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	TArray<AAzulTile*> Tiles;
};
