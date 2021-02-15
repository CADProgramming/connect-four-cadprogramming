// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "GridStopper.generated.h"

/**
 * 
 */
UCLASS()
class CONNECTFOUR_API AGridStopper : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isOpen;
	
};
