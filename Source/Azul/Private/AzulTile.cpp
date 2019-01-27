// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulTile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "TileType.h"
#include "Tile.h"

AAzulTile::AAzulTile()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AAzulTile::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AAzulTile::OnFingerPressedBlock);
}

void AAzulTile::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void AAzulTile::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AAzulTile::HandleClicked()
{
	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		// BlockMesh->SetMaterial(0, OrangeMaterial);
	}
}

void AAzulTile::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		//BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		//BlockMesh->SetMaterial(0, BlueMaterial);
	}
}

UTile* AAzulTile::GetTile() const
{
	return Tile;
}

void AAzulTile::SetTile(UTile* TileToSet)
{
	Tile = TileToSet;
	if (TileToSet)
	{
		BlockMesh->SetMaterial(0, TileToSet->GetTileType()->GetMaterialInstance());
	}
}

UTileType* AAzulTile::GetTileType() const
{
	return Tile->GetTileType();
}
