// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"
#include "Coin.generated.h"

UCLASS()
class CONNECTFOUR_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:
	// Distance from this coin to the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Position")
	float DistanceToGrid;

	// X position where the coin was picked up
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Position")
	float InitialXPosition;

	// Default coin mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	class UStaticMeshComponent* BlockMesh;

	// Default base material
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	class UMaterial* BaseMaterial;

	// Default glow material
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	class UMaterial* GlowMaterial;

	// Platform the coin cannot pass through
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Overlap Objects")
	class AStaticMeshActor* Platform;

	ACoin();

	// Left mouse button down on coin, move coin to mouse cursor
	void HandleClicked(const FVector MousePosition);

	// Left mouse button released, activate normal physics
	void HandleReleased();

	// Coin glow on mouse hover
	void Highlight(const bool bOn);
};
