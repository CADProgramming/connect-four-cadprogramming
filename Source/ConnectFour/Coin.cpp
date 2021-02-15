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
			: CoinMesh(TEXT("/Game/Geometry/Meshes/Grid/connect_four_coin"))
			, BaseMaterial(TEXT("/Game/Geometry/Meshes/Grid/CoinMaterial"))
			, GlowMaterial(TEXT("/Game/Geometry/Meshes/Grid/GlowMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.CoinMesh.Get());
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	RootComponent = BlockMesh;
	BlockMesh->SetSimulatePhysics(true);

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	GlowMaterial = ConstructorStatics.GlowMaterial.Get();
}

void ACoin::CoinClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ACoin::HandleClicked()
{
	BlockMesh->SetSimulatePhysics(false);
	SetActorLocation(MousePosition, false, nullptr, ETeleportType::None);
	SetActorRotation(FQuat(0, 0, 0.707f, 0.707f), ETeleportType::ResetPhysics);
}

void ACoin::HandleReleased()
{
	BlockMesh->SetSimulatePhysics(true);
}

void ACoin::Highlight(bool bOn)
{
	if (bOn)
	{
		BlockMesh->SetMaterial(0, GlowMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
}
