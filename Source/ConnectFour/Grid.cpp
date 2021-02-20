// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Coin.h"
#include "DrawDebugHelpers.h"


AGrid::AGrid()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorScale3D(FVector(0.2f, 5.2f, 3.74f));
    OnActorBeginOverlap.AddDynamic(this, &AGrid::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AGrid::OnOverlapEnd);
}

void AGrid::BeginPlay()
{
    Super::BeginPlay();

}

void AGrid::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (CoinAddedToGrid && CoinAddedToGrid->bIsNewInGrid && !CoinAddedToGrid->bIsMouseFocus)
    {
        FVector CoinVelocity = CoinAddedToGrid->GetVelocity();

        if (FMath::IsNearlyZero(CoinVelocity.Z, 0.1f) &&
            FMath::IsNearlyZero(CoinVelocity.Y, 0.1f) &&
            FMath::IsNearlyZero(CoinVelocity.X, 0.1f))
        {
            FVector CoinCoordinates = CoinAddedToGrid->GetActorLocation();
            float GridXPosition = FMath::RoundToInt((CoinCoordinates.Y - ORIGINX) / COLUMNWIDTH);
            float GridYPosition = FMath::RoundToInt((CoinCoordinates.Z - ORIGINY) / ROWHEIGHT);

            CoinLocation = FVector2D(GridXPosition, GridYPosition);
            CoinAddedToGrid->bIsNewInGrid = false;
            CoinAddedToGrid = nullptr;
        }
    }
}

void AGrid::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        ACoin* NewCoin = Cast<ACoin>(OtherActor);

        if (NewCoin->bIsNewInGrid)
        {
            CoinAddedToGrid = NewCoin;
            CoinAddedToGrid->bIsActive = false;
        }
        NewCoin = nullptr;
    }
}

void AGrid::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this) && CoinAddedToGrid && CoinAddedToGrid->GetActorLocation().Z > 0)
    {
        CoinAddedToGrid->bIsActive = true;
        CoinAddedToGrid = nullptr;
    }
}