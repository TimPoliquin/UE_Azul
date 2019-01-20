// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileType.generated.h"

/**
 * 
 */
class UMaterialInstance;
UCLASS()
class AZUL_API UTileType : public UObject
{
	GENERATED_BODY()

public:
	
	void Initialize(FName NameToSet, UMaterialInstance* MaterialInstanceToSet);
	FName GetName() const;
	UMaterialInstance* GetMaterialInstance() const;

private:
	FName Name;
	UPROPERTY()
	class UMaterialInstance* Material;
	
};
