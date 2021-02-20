// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"


// Sets default values
ACoin::ACoin()
{
	// Create and setup static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	RootComponent = BlockMesh;

	//Enable physics
	BlockMesh->SetSimulatePhysics(true);

	bIsNewInGrid = true;
	bIsActive = true;
	bIsMouseFocus = false;
}

// Left mouse button down on coin, move coin to mouse cursor
void ACoin::HandleClicked(const FVector MousePosition)
{
	// Move coin to mouse coordinates, enable collisions on move
	BlockMesh->SetSimulatePhysics(false);
	SetActorLocation(MousePosition, false, nullptr, ETeleportType::None);
	SetActorRotation(FQuat(0, 0, 0.707f, 0.707f), ETeleportType::ResetPhysics);
}

// Left mouse button released, activate normal physics
void ACoin::HandleReleased()
{
	// Restore normal physics
	BlockMesh->SetSimulatePhysics(true);
}

// Coin glow on mouse hover
void ACoin::Highlight(const bool bOn)
{
	// If glow enabled, use glow material
	if (bOn)
	{
		BlockMesh->SetMaterial(0, GlowMaterial);
		bIsMouseFocus = true;
	}
	else
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
		bIsMouseFocus = false;
	}
}
