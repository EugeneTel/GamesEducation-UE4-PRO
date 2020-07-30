// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeControlComponent.h"
#include "Log.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UTimeControlComponent::UTimeControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// setup defaults
	TimeEffectLength = 5.f;
	TimeDownImpact = 0.33f;
	TimeUpImpact = 2.f;
	bTimeEffectActive = false;
}

// Called when the game starts
void UTimeControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTimeControlComponent::TimeEffectBegin(const float Impact)
{
	// Don't allow multiple time effects
	if (bTimeEffectActive)
		return;

	ULog::Warning("Lets doo itt", LO_Both);
	bTimeEffectActive = true;
	
	UGameplayStatics::SetGlobalTimeDilation(this, Impact);
	
	GetOwner()->CustomTimeDilation = 1.f / Impact;

	// Correct time effect length according to time dilation
	const float EffectLengthWithDilation = TimeEffectLength * Impact;
	
	FTimerHandle TimeEffectTH;
	GetWorld()->GetTimerManager().SetTimer(TimeEffectTH, this, &UTimeControlComponent::OnTimeEffectEnd, EffectLengthWithDilation, false);
}

void UTimeControlComponent::Init(UInputComponent* InputComp)
{
	FKey TimeDownKey("Q");
	InputComp->BindKey(TimeDownKey, IE_Pressed, this, &UTimeControlComponent::OnTimeDownBegin);

	FKey TimeUpKey("E");
	InputComp->BindKey(TimeUpKey, IE_Pressed, this, &UTimeControlComponent::OnTimeUpBegin);
}

void UTimeControlComponent::OnTimeDownBegin()
{
	TimeEffectBegin(TimeDownImpact);
}

void UTimeControlComponent::OnTimeUpBegin()
{
	TimeEffectBegin(TimeUpImpact);
}

void UTimeControlComponent::OnTimeEffectEnd()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
	GetOwner()->CustomTimeDilation = 1.f;

	bTimeEffectActive = false;
}

