// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBoard.h"
#include "Wall.h"
#include "AzulGameMode.h"
#include "PatternLine.h"

// Sets default values
APlayerBoard::APlayerBoard()
{
}

bool APlayerBoard::CanAddTilesToLine(int32 LineNum, UTileType* TileType)
{
	// Is the line empty or does it have that type already?
	// Does the Wall already have that tile on that line?
	return false;
}

void APlayerBoard::AddTilesToLine(int32 LineNum, TArray<UTile*> Tiles)
{
	// Add Tiles to line
	// Move/Spawn actors and attach to sockets
}

void APlayerBoard::AddTilesToFloor(TArray<UTile*> Tiles)
{
	// Add tiles to floor
	// Move/Spawn actors and attach to sockets
}

void APlayerBoard::OnRoundEnd()
{
	// For each row (starting at the top):
		// If the row is complete:
			// Move first tile into position on the wall
			// Calculate score increase and add to score
			// Move other tiles into the Box
	// For each tile on FloorLine
		// Subtract points
		// If normal tile, move to Box
		// If [1] tile, return to Center
}

void APlayerBoard::Initialize(AAzulGameMode* GameModeToSet)
{
	GameMode = GameModeToSet;
	// Build the wall!
	Wall = NewObject<UWall>();
	Wall->Initialize(GameMode->GetTileTypes());
	// Create the Pattern Lines
	for (uint32 LineIdx = 1; LineIdx <= 5; LineIdx++)
	{
		UPatternLine* PatternLine = NewObject<UPatternLine>();
		PatternLine->SetSize(LineIdx);
		PatternLines.Add(PatternLine);
	}
}

void APlayerBoard::AddTileToWall(int32 LineNum, UTile* Tile)
{

}

bool APlayerBoard::IsWallComplete() const
{
	return Wall->IsComplete();
}

