// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DirectionalLight.h"
#include "ConnectFourPawn.h"
#include "ConnectFourPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AConnectFourPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AConnectFourPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
	TSubclassOf<AActor> SkySphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
	class ADirectionalLight* Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	class AActor* Player1Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	class AActor* P1ToP2Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	class AActor* Player2Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	class AActor* P2ToP1Cam;

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
};


