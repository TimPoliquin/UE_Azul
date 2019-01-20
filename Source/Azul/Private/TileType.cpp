// Fill out your copyright notice in the Description page of Project Settings.

#include "TileType.h"
#include "Materials/MaterialInstance.h"

void UTileType::Initialize(FName NameToSet, UMaterialInstance* MaterialInstanceToSet)
{
	Name = NameToSet;
	Material = MaterialInstanceToSet;
}

FName UTileType::GetName() const
{
	return Name;
}

UMaterialInstance* UTileType::GetMaterialInstance() const
{
	return Material;
}