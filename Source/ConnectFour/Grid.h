// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Grid.generated.h"

/**
 * 
 */
UCLASS()
class CONNECTFOUR_API AGrid : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ACoin* CoinAddedToGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector CoinLocation;

	// constructor sets default values for this actor's properties
	AGrid();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	virtual void Tick(float DeltaSeconds) override;
};
