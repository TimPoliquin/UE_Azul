// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AzulFactory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFactorySelectionStarted, AAzulFactory*, Factory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFactorySelectionCancelled, AAzulFactory*, Factory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFactorySendTilesToCenter, const TArray<AAzulTile*>, Tiles);


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

	void PopulateTiles(TArray<AAzulTile*> TilesToAdd);
	TArray<AAzulTile*> PullSelectedTiles();
	bool GetIsCenter() const;
	void SetIsCenter(bool ToSet);
	void ResetTileSelection();

	FFactorySelectionStarted OnFactorySelectionStarted;
	FFactorySelectionCancelled OnFactorySelectionCancelled;
	FFactorySendTilesToCenter OnFactorySendTilesToCenter;

private:
	bool IsCenter = false;
	TArray<AAzulTile*> Tiles;
	TArray<AAzulTile*> SelectedTiles;
	
	UFUNCTION() // To support delegate binding
	void OnTileClicked(AAzulTile* ClickedTile);
	void SelectTiles(UTileType* TileType);
};
