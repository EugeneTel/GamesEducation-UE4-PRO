// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamesEducation/_Homework/HW_03_Delegates/DynamicTurret.h"

#include "CurveTurret.generated.h"

UCLASS()
class GAMESEDUCATION_API ACurveTurret : public ADynamicTurret
{
	GENERATED_BODY()


public:	

	/** Curve class for the Spline component building */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector* CurveRoute;


	void OnConstruction(const FTransform& Transform) override;

	/** Try to adjust Spline component points to a Curve */
	void SetSplinePoints(UCurveVector* Curve);


protected:
	void SetupMovementRoute() const override;
};
