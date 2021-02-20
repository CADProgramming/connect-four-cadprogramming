// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"


AGrid::AGrid()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorScale3D(FVector(0.2f, 5.2f, 3.73f));
    
    OnActorBeginOverlap.AddDynamic(this, &AGrid::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AGrid::OnOverlapEnd);

    SetupGrid();
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

        if (FMath::IsNearlyZero(CoinVelocity.Z, 1.0f) &&
            FMath::IsNearlyZero(CoinVelocity.Y, 1.0f) &&
            FMath::IsNearlyZero(CoinVelocity.X, 1.0f))
        {
            FVector CoinCoordinates = CoinAddedToGrid->GetActorLocation();
            float GridXPosition = FMath::RoundToInt((CoinCoordinates.Y - ORIGINX) / COLUMNWIDTH);
            float GridYPosition = FMath::RoundToInt((CoinCoordinates.Z - ORIGINY) / ROWHEIGHT);

            CoinLocation = FVector2D(GridXPosition, GridYPosition);

            ECoinType NewCoinType = CoinAddedToGrid->TypeOfCoin;

            Grid[(int32)CoinLocation.X][(int32)CoinLocation.Y] = NewCoinType;
            CoinAddedToGrid->bIsNewInGrid = false;
            CoinAddedToGrid = nullptr;

            CheckConnectFour(CoinLocation, NewCoinType);
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
    if (OtherActor && (OtherActor != this) && CoinAddedToGrid)
    {
        if (CoinAddedToGrid->GetActorLocation().Z > 0)
        {
            CoinAddedToGrid->bIsActive = true;
            CoinAddedToGrid = nullptr;
        }
        else
        {
            SetupGrid();
        }
    }
}

void AGrid::SetupGrid()
{
    if (Grid.Num() > 0)
    {
        for (int x = 0; x < GRIDWIDTH; x++)
        {
            Grid[x].Empty();
        }
        Grid.Empty();
    }

    TArray<ECoinType> GridRow = TArray<ECoinType>();
    for (int y = 0; y < GRIDHEIGHT; y++)
    {
        GridRow.Add(ECoinType::NONE);
    }
    for (int x = 0; x < GRIDWIDTH; x++)
    {
        Grid.Add(GridRow);
    }
}

void AGrid::CheckConnectFour(FVector2D NewCoinLocation, ECoinType CoinColour)
{
    int LeftHorizontalCount = 0;
    int RightHorizontalCount = 0;
    int HorizontalCount = 0;
    int VerticalCount = 0;

    // Left Horizontal Count
    for (int c = 0; c < 4; c++)
    {
        if (NewCoinLocation.X - c >= 0 && NewCoinLocation.Y - c >= 0)
        {
            if (Grid[NewCoinLocation.X - c][NewCoinLocation.Y - c] == CoinColour)
            {
                LeftHorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }
    for (int c = 1; c < 4; c++)
    {
        if (NewCoinLocation.X + c < GRIDWIDTH && NewCoinLocation.Y + c < GRIDHEIGHT)
        {
            if (Grid[NewCoinLocation.X + c][NewCoinLocation.Y + c] == CoinColour)
            {
                LeftHorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }

    // Right Horizontal Count
    for (int c = 0; c < 4; c++)
    {
        if (NewCoinLocation.X + c < GRIDWIDTH && NewCoinLocation.Y - c >= 0)
        {
            if (Grid[NewCoinLocation.X + c][NewCoinLocation.Y - c] == CoinColour)
            {
                RightHorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }
    for (int c = 1; c < 4; c++)
    {
        if (NewCoinLocation.X - c >= 0 && NewCoinLocation.Y + c < GRIDHEIGHT)
        {
            if (Grid[NewCoinLocation.X - c][NewCoinLocation.Y + c] == CoinColour)
            {
                RightHorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }

    // Horizontal Count
    for (int c = 0; c < 4; c++)
    {
        if (NewCoinLocation.X + c < GRIDWIDTH)
        {
            if (Grid[NewCoinLocation.X + c][NewCoinLocation.Y] == CoinColour)
            {
                HorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }
    for (int c = 1; c < 4; c++)
    {
        if (NewCoinLocation.X - c >= 0)
        {
            if (Grid[NewCoinLocation.X - c][NewCoinLocation.Y] == CoinColour)
            {
                HorizontalCount++;
            }
            else
            {
                break;
            }
        }
    }

    // Vertical Count
    for (int c = 0; c < 4; c++)
    {
        if (NewCoinLocation.Y + c < GRIDHEIGHT)
        {
            if (Grid[NewCoinLocation.X][NewCoinLocation.Y + c] == CoinColour)
            {
                VerticalCount++;
            }
            else
            {
                break;
            }
        }
    }
    for (int c = 1; c < 4; c++)
    {
        if (NewCoinLocation.Y - c >= 0)
        {
            if (Grid[NewCoinLocation.X][NewCoinLocation.Y - c] == CoinColour)
            {
                VerticalCount++;
            }
            else
            {
                break;
            }
        }
    }

    if (LeftHorizontalCount >= 4 ||
        RightHorizontalCount >= 4 ||
        HorizontalCount >= 4 ||
        VerticalCount >= 4)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Connect Four!"), true, FVector2D(3.0f, 3.0f));
        }
    }
}