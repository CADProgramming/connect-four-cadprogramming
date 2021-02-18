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
	// Current coin that is clicked on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ACoin* CurrentCoinFocus;

	// Current location of mouse cursor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector MousePosition;

	// Tick event for Pawn
	virtual void Tick(float DeltaSeconds) override;

	// Binds Mouse axis to Grab Coin method
    virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

protected:
	// Calculates a mouse position that conforms to the coin's x coordinate
	void CalculateMousePosition(const FVector TraceStart, const FVector TraceEnd);

	// Makes a trace from the camera to the nearest coin using the mouse for direction
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	// Initiates a mouse drag using the coin under the mouse
	void GrabCoin(float AxisValue);

private:
	const float MINMOVEHEIGHT = 200.0f;
	const float MAXMOVEHEIGHT = 350.0f;
	const float MOVEHEIGHTDIFF = MAXMOVEHEIGHT - MINMOVEHEIGHT;

	const float GRIDXPOSITION = 0;
};
