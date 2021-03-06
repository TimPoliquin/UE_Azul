// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AzulTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileClickDelegate, AAzulTile*, ClickedTile);


class UTile;
class UTileType;
/** A block that can be clicked */
UCLASS(minimalapi)
class AAzulTile : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:

	AAzulTile();

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	void HandleClicked();
	void Select(bool bOn);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

	UTile* GetTile() const;
	void SetTile(UTile* TileToSet);
	UTileType* GetTileType() const;

	bool GetIsSelected() const;

	FTileClickDelegate OnTileClick;

private:
	UTile* Tile;
	bool IsSelected;

};



