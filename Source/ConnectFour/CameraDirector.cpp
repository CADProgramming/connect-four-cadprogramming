// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "ConnectFourPlayerController.h"
#include "GridStopper.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* RawPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (RawPlayerController)
	{
		PlayerController = Cast<AConnectFourPlayerController>(RawPlayerController);
		PlayerController->VisualsManager = this;
	}
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CameraMoveTime >= 0)
    {
        CameraMoveTime -= DeltaTime;
    }
    else
    {
        FOutputDevice* ar = nullptr;
        SkySphere->CallFunctionByNameWithArguments(TEXT("SlowCloudSpeed"), *ar, NULL, true);
    }

    if (PlayerController && TransitionTime >= 0)
    {
        TransitionTime -= DeltaTime;
        MoveSun();
    }
    else if (TransitionTime <= 0)
    {
        if (Player1Cam && PlayerController->GetViewTarget() != Player1Cam &&
            PlayerController->GetViewTarget() == P2ToP1Cam)
        {
            PlayerController->SetViewTargetWithBlend(Player1Cam, BLENDTIME);
        }

        if (Player2Cam && PlayerController->GetViewTarget() != Player2Cam &&
            PlayerController->GetViewTarget() == P1ToP2Cam)
        {
            PlayerController->SetViewTargetWithBlend(Player2Cam, BLENDTIME);
        }
    }
}

void ACameraDirector::SetCameraStart(AActor* NewCamera)
{
    if (PlayerController)
    {
        if (NewCamera && PlayerController->GetViewTarget() != NewCamera)
        {
            // Blend smoothly to camera two.
            PlayerController->SetViewTarget(NewCamera);
        }
    }
}

void ACameraDirector::ChangeCamera(AActor* NewCamera)
{
    if (PlayerController)
    {
        if (NewCamera && PlayerController->GetViewTarget() != NewCamera)
        {
            // Blend smoothly to camera two.
            PlayerController->SetViewTargetWithBlend(NewCamera, BLENDTIME);
            TransitionTime += BLENDTIME;
            CameraMoveTime += BLENDTIME * 2;

            FOutputDevice* ar = nullptr;
            SkySphere->CallFunctionByNameWithArguments(TEXT("FastCloudSpeed"), *ar, NULL, true);
        }
    }
}

void ACameraDirector::MoveSun()
{
    Sun->AddActorLocalRotation(FQuat(0, 0.0043633f, 0, 0.9999905f), false, nullptr, ETeleportType::None);
    FOutputDevice* ar = nullptr;
    SkySphere->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), *ar, NULL, true);
}

void ACameraDirector::TransitionToPlayer1()
{
    SetCameraStart(Player2Cam);
    ChangeCamera(P2ToP1Cam);
}

void ACameraDirector::TransitionToPlayer2()
{
    SetCameraStart(Player1Cam);
    ChangeCamera(P1ToP2Cam);
}

void ACameraDirector::CameraGameStart()
{
    SetCameraStart(Player1Cam);
}