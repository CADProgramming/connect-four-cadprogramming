// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "CoinType.h"
#include "Coin.generated.h"

UCLASS()
class CONNECTFOUR_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	bool bIsNewInGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	bool bIsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	bool bIsMouseFocus;

	// Distance from this coin to the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Position")
	float DistanceToGrid;

	// X position where the coin was picked up
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Position")
	float InitialXPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TEnumAsByte<ECoinType> TypeOfCoin;

	// Default coin mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	class UStaticMeshComponent* BlockMesh;

	// Default base material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	class UMaterial* BaseMaterial;

	// Default glow material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	class UMaterial* GlowMaterial;

	ACoin();

	// Left mouse button down on coin, move coin to mouse cursor
	void HandleClicked(const FVector MousePosition);

	// Left mouse button released, activate normal physics
	void HandleReleased();

	// Coin glow on mouse hover
	void Highlight(const bool bOn);

};
