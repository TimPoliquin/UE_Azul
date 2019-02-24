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
	OnTileClick.Broadcast(this);
}

void AAzulTile::Select(bool bOn)
{
	FVector CurrentLocation = GetActorLocation();
	if (bOn && !IsSelected)
	{
		SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 50.f));
	}
	else if(!bOn && IsSelected)
	{
		SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z - 50.f));
	}
	IsSelected = bOn;
}

bool AAzulTile::GetIsSelected() const
{
	return IsSelected;
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
