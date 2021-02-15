// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ConnectFourPawn.generated.h"

UCLASS(config=Game)
class AConnectFourPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

	void GrabCoin(float AxisValue);

	UPROPERTY(VisibleAnywhere)
	float distanceFromGrid;

	UPROPERTY(VisibleAnywhere)
	float currentXPosition;

protected:
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ACoin* CurrentCoinFocus;

	FVector MousePosition;
};
