// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerBoardTileSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileSelectorClickDelegate, int32, Row);

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), Blueprintable)
class AZUL_API UPlayerBoardTileSelector : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	FTileSelectorClickDelegate OnPlayerBoardTileSelected;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Setup")
	int32 Row;
	UPROPERTY(EditInstanceOnly, Category = "Setup")
	int32 Column;

private:
	UFUNCTION()
	void HandleOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
