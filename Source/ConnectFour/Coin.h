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

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	/** Are we currently active? */
	bool isActive;

	UPROPERTY(VisibleAnywhere)
	FVector MousePosition;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
	class UMaterial* GlowMaterial;

	UPROPERTY(VisibleAnywhere)
	AStaticMeshActor* Platform;

	UFUNCTION()
	void CoinClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();
	void HandleReleased();

	void Highlight(bool bOn);
	void UpdateMousePosition(FVector CurrentMousePosition) { MousePosition = CurrentMousePosition; }
};
