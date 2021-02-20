// Copyright Epic Games, Inc. All Rights Reserved.


#include "ConnectFourPawn.h"


AConnectFourPawn::AConnectFourPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Player controller should use this pawn
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Tick event for Pawn
void AConnectFourPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End, false);

		CalculateMousePosition(Start, End);
	}
}

// Binds Mouse axis to Grab Coin method
void AConnectFourPawn::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis("GrabCoin", this, &AConnectFourPawn::GrabCoin);
}

// Calculates a mouse position that conforms to the coin's x coordinate
void AConnectFourPawn::CalculateMousePosition(const FVector TraceStart, const FVector TraceEnd)
{
	// Make sure there is a coin in focus
	if (CurrentCoinFocus)
	{
		float& InitialXPositionPtr = CurrentCoinFocus->InitialXPosition;
		float& DistanceToGridPtr = CurrentCoinFocus->DistanceToGrid;

		// If mouse is above minimum move height
		if (MousePosition.Z >= MINMOVEHEIGHT)
		{
			// If mouse isn't already at the top of the grid
			if (MousePosition.Z <= MAXMOVEHEIGHT)
			{
				// Calculate the x position based on the height of the coin, higher coin == closer to grid
				MousePosition.X = InitialXPositionPtr + (DistanceToGridPtr * ((MousePosition.Z - MINMOVEHEIGHT) / MOVEHEIGHTDIFF));
			}
			else
			{
				// Coin can drop into grid
				MousePosition.X = GRIDXPOSITION;
			}
		}
		else
		{
			// Don't move coin toward grid
			MousePosition.X = CurrentCoinFocus->GetTargetLocation().X;
			InitialXPositionPtr = MousePosition.X;
			DistanceToGridPtr = GRIDXPOSITION - InitialXPositionPtr;
		}

		// Calculate mouse Y and Z coordinates based on perspective using a fixed X position
		MousePosition.Y = (((TraceEnd.Y - TraceStart.Y) / (TraceEnd.X - TraceStart.X))
			* (MousePosition.X - TraceStart.X)) + TraceStart.Y;
		MousePosition.Z = (((TraceEnd.Z - TraceStart.Z) / (TraceEnd.X - TraceStart.X)) 
			* (MousePosition.X - TraceStart.X)) + TraceStart.Z;
	}
}

// Makes a trace from the camera to the nearest coin using the mouse for direction
void AConnectFourPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	// Left mouse button is not down
	if (GetInputAxisValue("GrabCoin") != 1.0f)
	{
		// Start a trace for a coin
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
		
		// Debug
		if (bDrawDebugHelpers)
		{
			DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
			DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
		}

		// If coin is found
		if (HitResult.Actor.IsValid())
		{
			// Cast to coin
			ACoin* HitCoin = Cast<ACoin>(HitResult.Actor.Get());

			// If Coin is marked as active
			if (HitCoin && HitCoin->bIsActive)
			{
				// If coin is not the same as previous
				if (CurrentCoinFocus != HitCoin)
				{
					// Unhighlight previous coin
					if (CurrentCoinFocus)
					{
						CurrentCoinFocus->Highlight(false);
					}

					// Highlight current coin
					HitCoin->Highlight(true);
					CurrentCoinFocus = HitCoin;
				}
			}
			else if (CurrentCoinFocus) // Can't select coin because not active
			{
				CurrentCoinFocus->Highlight(false);
				CurrentCoinFocus = nullptr;
			}
		}
		else if (CurrentCoinFocus)
		{
			CurrentCoinFocus->Highlight(false);
			CurrentCoinFocus = nullptr;
		}
	}
}

// Initiates a mouse drag using the coin under the mouse
void AConnectFourPawn::GrabCoin(float AxisValue)
{
	// Left mouse button clicked
	if (CurrentCoinFocus && AxisValue == 1.0f)
	{
		// Handle click event
		CurrentCoinFocus->HandleClicked(MousePosition);
	}
	else if (CurrentCoinFocus && AxisValue == 0)
	{
		CurrentCoinFocus->HandleReleased();
	}
}