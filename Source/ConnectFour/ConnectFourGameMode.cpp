// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConnectFourGameMode.h"
#include "ConnectFourPlayerController.h"
#include "ConnectFourPawn.h"

AConnectFourGameMode::AConnectFourGameMode()
{
	// no pawn by default
	DefaultPawnClass = AConnectFourPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AConnectFourPlayerController::StaticClass();
}
