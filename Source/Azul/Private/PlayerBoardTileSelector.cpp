// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBoardTileSelector.h"

void UPlayerBoardTileSelector::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddUniqueDynamic(this, &UPlayerBoardTileSelector::HandleOnClicked);
}

void UPlayerBoardTileSelector::HandleOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnPlayerBoardTileSelected.Broadcast(Row);
}