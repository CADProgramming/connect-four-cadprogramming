// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConnectFourPawn.h"
#include "Coin.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AConnectFourPawn::AConnectFourPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AConnectFourPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End, false);

		if (CurrentCoinFocus)
		{
			if (MousePosition.Z >= 200.0f)
			{
				if (MousePosition.Z <= 350.0f)
				{
					MousePosition.X = currentXPosition + (distanceFromGrid * ((MousePosition.Z - 200.0f) / 150.0f));
				}
				else
				{
					MousePosition.X = 940.0f;
				}
			}
			else
			{
				MousePosition.X = CurrentCoinFocus->GetTargetLocation().X;
				currentXPosition = MousePosition.X;
				distanceFromGrid = 940.0f - currentXPosition;
			}
			MousePosition.Y = (((End.Y - Start.Y) / (End.X - Start.X)) * (MousePosition.X - Start.X)) + Start.Y;
			MousePosition.Z = (((End.Z - Start.Z) / (End.X - Start.X)) * (MousePosition.X - Start.X)) + Start.Z;
			CurrentCoinFocus->UpdateMousePosition(MousePosition);
		}
	}
}

// Called to bind functionality to input
void AConnectFourPawn::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis("GrabCoin", this, &AConnectFourPawn::GrabCoin);
}

void AConnectFourPawn::GrabCoin(float AxisValue)
{
	if (CurrentCoinFocus && AxisValue == 1.0f)
	{
		CurrentCoinFocus->HandleClicked();
	}
	else if (CurrentCoinFocus && AxisValue == 0)
	{
		CurrentCoinFocus->HandleReleased();
	}
}

void AConnectFourPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	if (GetInputAxisValue("GrabCoin") != 1.0f)
	{
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
		if (bDrawDebugHelpers)
		{
			DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
			DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
		}
		if (HitResult.Actor.IsValid())
		{
			ACoin* HitBlock = Cast<ACoin>(HitResult.Actor.Get());

			if (CurrentCoinFocus != HitBlock)
			{
				if (CurrentCoinFocus)
				{
					CurrentCoinFocus->Highlight(false);
				}
				if (HitBlock)
				{
					HitBlock->Highlight(true);
				}
				CurrentCoinFocus = HitBlock;
			}
		}
		else if (CurrentCoinFocus)
		{
			CurrentCoinFocus->Highlight(false);
			CurrentCoinFocus = nullptr;
		}
	}
}