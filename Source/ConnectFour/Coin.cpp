// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

// Sets default values
ACoin::ACoin()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> CoinMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GlowMaterial;
		FConstructorStatics()
			: CoinMesh(TEXT("/Game/Geometry/Meshes/Coin/Coin"))
			, BaseMaterial(TEXT("/Game/Geometry/Meshes/Coin/CoinMaterial"))
			, GlowMaterial(TEXT("/Game/Geometry/Meshes/Coin/GlowMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create and setup static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.CoinMesh.Get());
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	RootComponent = BlockMesh;

	//Enable physics
	BlockMesh->SetSimulatePhysics(true);

	//Setup material defaults
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	GlowMaterial = ConstructorStatics.GlowMaterial.Get();
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
	}
	else
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
}
