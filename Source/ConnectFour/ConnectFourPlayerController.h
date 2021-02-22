// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DirectionalLight.h"
#include "ConnectFourPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AConnectFourPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AConnectFourPlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class ACameraDirector* VisualsManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	bool bPlayer1Turn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class AConnectFourPawn* Player1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class AConnectFourPawn* Player2;

	// Changes the turn to the next player
	void ChangeTurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Transitions from player 2 to player 1's turn
	void TransitionToPlayer1();

	// Transitions from player 1 to player 2's turn
	void TransitionToPlayer2();

	void CameraGameStart();
};


