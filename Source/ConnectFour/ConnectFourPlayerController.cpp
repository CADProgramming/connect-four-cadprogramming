// Copyright Epic Games, Inc. All Rights Reserved.


#include "ConnectFourPlayerController.h"
#include "ConnectFourPawn.h"
#include "CameraDirector.h"

AConnectFourPlayerController::AConnectFourPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bPlayer1Turn = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AConnectFourPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Player1 = GetWorld()->SpawnActor<AConnectFourPawn>(AConnectFourPawn::StaticClass());
	Player2 = GetWorld()->SpawnActor<AConnectFourPawn>(AConnectFourPawn::StaticClass());

	Player1->MyColour = ECoinType::RED_COIN;
	Player2->MyColour = ECoinType::YELLOW_COIN;

	Possess(Player1);
}

void AConnectFourPlayerController::ChangeTurn()
{
	bPlayer1Turn = !bPlayer1Turn;
	UnPossess();

	if (bPlayer1Turn)
	{
		Possess(Player1);
		TransitionToPlayer1();
	}
	else
	{
		Possess(Player2);
		TransitionToPlayer2();
	}
}

void AConnectFourPlayerController::TransitionToPlayer1()
{
	if (VisualsManager)
	{
		VisualsManager->TransitionToPlayer1();
	}
}

void AConnectFourPlayerController::TransitionToPlayer2()
{
	if (VisualsManager)
	{
		VisualsManager->TransitionToPlayer2();
	}
}