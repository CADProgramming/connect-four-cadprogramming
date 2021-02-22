// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConnectFourGameMode.h"
#include "ConnectFourPlayerController.h"
#include "ConnectFourPawn.h"

AConnectFourGameMode::AConnectFourGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AConnectFourPlayerController::StaticClass();
}
