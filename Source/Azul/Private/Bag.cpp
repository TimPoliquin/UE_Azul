// Fill out your copyright notice in the Description page of Project Settings.

#include "Bag.h"
#include "Tile.h"
#include "AzulTile.h"

UWorld* UBag::GetWorld() const
{
	return World;
}

void UBag::SetWorld(UWorld* WorldToSet)
{
	World = WorldToSet;
}

TArray<AAzulTile*> UBag::Draw(int32 NumToDraw)
{
	TArray<AAzulTile*> TilesDrawn;
	if (NumToDraw > Tiles.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to draw too many tiles from the bag!"))
	}
	for (int32 Idx = 0; Idx < NumToDraw && Tiles.Num() > 0; Idx++)
	{
		UTile* Tile = Tiles.Pop();
		AAzulTile* TileDrawn = Tile->CreateActor(World);
		if (TileDrawn)
		{
			TilesDrawn.Push(TileDrawn);
		}
	}
	return TilesDrawn;
}

void UBag::Return(TArray<UTile*> TilesToReturn)
{
	Tiles.Append(TilesToReturn);
	Shuffle();
}

int32 UBag::GetNumTilesRemaining() const
{
	return Tiles.Num();
}

void UBag::Shuffle()
{
	for (int32 Idx = Tiles.Num() - 1; Idx > 0; Idx--)
	{
		int32 NewIdx = FMath::FloorToInt(FMath::SRand() * (Idx + 1)) % Tiles.Num();
		UTile* Temp = Tiles[Idx];
		Tiles[Idx] = Tiles[NewIdx];
		Tiles[NewIdx] = Temp;
	}
}