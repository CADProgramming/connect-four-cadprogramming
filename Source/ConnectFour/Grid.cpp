// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Coin.h"
#include "DrawDebugHelpers.h"


AGrid::AGrid()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorScale3D(FVector(0.2f, 5.2f, 3.75f));
    OnActorBeginOverlap.AddDynamic(this, &AGrid::OnOverlapBegin);
}

void AGrid::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AGrid::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (CoinAddedToGrid)
    {
        CoinLocation = CoinAddedToGrid->GetActorLocation();
    }
}

void AGrid::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this) && OtherActor != CoinAddedToGrid)
    {
        CoinAddedToGrid = Cast<ACoin>(OtherActor);
    }
}