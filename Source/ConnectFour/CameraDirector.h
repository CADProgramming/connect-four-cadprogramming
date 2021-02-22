// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "CameraDirector.generated.h"

UCLASS()
class CONNECTFOUR_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
	class AActor* SkySphere;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AGridStopper* Switch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AConnectFourPlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TransitionTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CameraMoveTime;

	// Sets default values for this actor's properties
	ACameraDirector();

	// Transitions from player 2 to player 1's turn
	void TransitionToPlayer1();

	// Transitions from player 1 to player 2's turn
	void TransitionToPlayer2();

	void CameraGameStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const float BLENDTIME = 1.2f;

	void SetCameraStart(AActor* NewCamera);
	void ChangeCamera(AActor* NewCamera);
	void MoveSun(float DeltaTime);

};
