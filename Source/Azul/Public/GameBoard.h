// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

class AAzulFactory;
class APlayerBoard;

UCLASS()
class AZUL_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBoard();

	void Initialize(int32 NumPlayers);
	int32 GetNumFactories(int32 NumPlayers) const;
	void PopulateFactories(TArray<UTile*> Bag);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	uint32 BoardRadius = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAzulFactory> FactoryBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlayerBoard> PlayerBoardBlueprint;

private:
	void CreateFactories(int32 NumPlayers);
	void CreatePlayerBoards(int32 NumPlayers);

	const int32 NumTilesPerFactory = 4;
	TArray<AAzulFactory*> Factories;


};
