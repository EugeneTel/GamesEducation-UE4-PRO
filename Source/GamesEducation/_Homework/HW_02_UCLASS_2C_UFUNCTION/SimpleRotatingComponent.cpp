// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRotatingComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USimpleRotatingComponent::USimpleRotatingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set a default value for the Rotation Speed
	RotationSpeed = 10.f;

	IsEnabled = true;
}


// Called when the game starts
void USimpleRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USimpleRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Rotate the Actor when rotation is active
	if (IsEnabled)
	{
		RotateTick(DeltaTime);
	}
}

void USimpleRotatingComponent::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleRotatingComponent::Interact_Implementation"));
}

/**
 * Rotate the Owner Actor every tick
 */
void USimpleRotatingComponent::RotateTick(float DeltaTime) const
{
	const FRotator AddRotation(RotationSpeed * DeltaTime);
	
	GetOwner()->AddActorWorldRotation(AddRotation);
}

