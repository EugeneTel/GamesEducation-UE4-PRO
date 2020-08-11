// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMaterialChange.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Curves/CurveFloat.h"

// Sets default values
AActorMaterialChange::AActorMaterialChange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AActorMaterialChange::BeginPlay()
{
	Super::BeginPlay();

	DynamicMatInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	RandomColor = GetRandomColor();

	SetColor(RandomColor);
}

// Called every frame
void AActorMaterialChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set color from curve
	if (ColorCurve)
	{
		const FLinearColor NewColor = GetCurveColor();
		SetColor(NewColor);
	}
}

void AActorMaterialChange::SetColor(const FLinearColor& NewColor) const
{
	// If we have a valid dynamic material instance - modify its parameters
	if (DynamicMatInstance)
	{
		DynamicMatInstance->SetVectorParameterValue(FName("ColorParam"), NewColor);
		DynamicMatInstance->SetScalarParameterValue(FName("MetParam"), FMath::RandRange(0.f, 1.f));
	}
}

FLinearColor AActorMaterialChange::GetRandomColor() const
{
	FLinearColor NewColor;
	NewColor.R = FMath::RandRange(0.f, 1.f);
	NewColor.G = FMath::RandRange(0.f, 1.f);
	NewColor.B = FMath::RandRange(0.f, 1.f);
	NewColor.A = FMath::RandRange(0.f, 1.f);

	return NewColor;
}

FLinearColor AActorMaterialChange::GetCurveColor()
{
	FLinearColor ResultColor = RandomColor;
	
	if (!ColorCurve)
		return ResultColor;


	// Get positive curve length
	if (!CurveLengthSeconds)
	{
		// Try to find curve time range for limits
		float MaxTime, MinTime;
		ColorCurve->GetTimeRange(MinTime, MaxTime);

		// use only positive values
		CurveLengthSeconds = MaxTime;
	}

	// Calculate current curve time point according to world time
	const float CurveTime = FGenericPlatformMath::Fmod(GetWorld()->GetTimeSeconds(), CurveLengthSeconds);

	// Change red channel according to curve
	ResultColor.R = ColorCurve->GetFloatValue(CurveTime);

	return ResultColor;
}


