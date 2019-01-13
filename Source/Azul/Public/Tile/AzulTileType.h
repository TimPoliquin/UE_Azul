#pragma once

#include "CoreMinimal.h"

/** A block that can be clicked */
class AzulTileType
{

public:
	enum class TileType : uint8
	{
		RED,
		BLACK,
		ORANGE,
		BLUE,
		WHITE
	};

	static TArray<TileType> TileTypes()
	{
		TArray<TileType> TileTypes;
		TileTypes.Add(TileType::RED);
		TileTypes.Add(TileType::BLACK);
		TileTypes.Add(TileType::ORANGE);
		TileTypes.Add(TileType::BLUE);
		TileTypes.Add(TileType::WHITE);
		return TileTypes;
	}

};