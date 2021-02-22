// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Coin.h"
#include "DrawDebugHelpers.h"
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
	FVector2D CoinLocation;

	TArray<TArray<ECoinType>> Grid;

	// constructor sets default values for this actor's properties
	AGrid();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	virtual void Tick(float DeltaSeconds) override;

private:
	const int ROWHEIGHT = -50;
	const int COLUMNWIDTH = 60;
	const int ORIGINX = -180;
	const int ORIGINY = 295;

	const int GRIDWIDTH = 7;
	const int GRIDHEIGHT = 6;

	void SetupGrid();
	bool CheckConnectFour(FVector2D NewCoinLocation, ECoinType CoinColour);
};
