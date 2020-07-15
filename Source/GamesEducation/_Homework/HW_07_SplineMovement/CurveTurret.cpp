// Fill out your copyright notice in the Description page of Project Settings.


#include "CurveTurret.h"
#include "Curves/CurveVector.h"
#include "Log.h"

void ACurveTurret::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    ensureMsgf(CurveRoute, TEXT("Curve is not set for the CurveTurret!!!"));

    if (CurveRoute)
    {
        SetSplinePoints(CurveRoute);
    }
}

void ACurveTurret::SetSplinePoints(UCurveVector* Curve)
{
    SplineComp->ClearSplinePoints();

    // Add a new point for each 0.2 second
    const float OnePointTime = 0.2;

    // Add some limits for preventing infinite loop
    const int MaxPoints = 1000;

    // Try to find curve time range for limits
    float MaxTime, MinTime;
    Curve->GetTimeRange(MinTime, MaxTime);

    float CurrentPointTime = 0.f;
    int PointsNumber = 0;

    // represent curve as a list of time points and go through points
    while (CurrentPointTime < MaxTime)
    {
        // add a new spline point according to curve
        FVector NewPoint = Curve->GetVectorValue(CurrentPointTime);
        SplineComp->AddSplinePoint(NewPoint, ESplineCoordinateSpace::Local, false);

        // out of range protector
        CurrentPointTime += OnePointTime;
        if (CurrentPointTime > MaxTime)
            CurrentPointTime = MaxTime;

        // infinite loop protector
        PointsNumber++;
        if (PointsNumber > MaxPoints)
        {
            UE_LOG(LogTemp, Warning, TEXT("Maximum curve points was reached!!!"));
            break;
        }

    }

    SplineComp->UpdateSpline();
    
    ULog::Number(PointsNumber, "Total points: ");
}

void ACurveTurret::SetupMovementRoute() const
{
    Super::SetupMovementRoute();
}
