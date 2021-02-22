// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "ConnectFourPlayerController.h"


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
		AConnectFourPlayerController* PlayerController = Cast<AConnectFourPlayerController>(RawPlayerController);
		PlayerController->VisualsManager = this;
	}
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraDirector::ChangeCamera(AActor* NewCamera)
{
    // Find the actor that handles control for the local player.
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        if (NewCamera && PlayerController->GetViewTarget() != NewCamera)
        {
            // Blend smoothly to camera two.
            PlayerController->SetViewTargetWithBlend(NewCamera, BLENDTIME);
        }
    }
}

void ACameraDirector::TransitionToPlayer1()
{
    ChangeCamera(Player1Cam);
}

void ACameraDirector::TransitionToPlayer2()
{
    ChangeCamera(Player2Cam);
}