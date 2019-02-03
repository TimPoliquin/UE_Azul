// Fill out your copyright notice in the Description page of Project Settings.

#include "PatternLine.h"
#include "AzulGameMode.h"
#include "Wall.h"

void UPatternLine::SetSize(int32 SizeToSet)
{
	Size = SizeToSet;
}

TArray<UTile*> UPatternLine::AddTiles(TArray<UTile*> TilesToAdd)
{
	while (Tiles.Num() < Size)
	{
		Tiles.Add(TilesToAdd.Pop());
		// Need to move the rendered tile, too
	}
	return TilesToAdd;
}

bool UPatternLine::IsComplete() const
{
	return Tiles.Num() == Size;
}

void UPatternLine::OnRoundEnd(UWall* Wall, AAzulGameMode* GameMode)
{
	if (IsComplete())
	{
		Wall->AddTile(Size, Tiles.Pop());
		GameMode->ReturnToBox(Tiles);
	}
}