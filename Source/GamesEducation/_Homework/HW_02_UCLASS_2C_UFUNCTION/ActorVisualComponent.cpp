// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorVisualComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values for this component's properties
UActorVisualComponent::UActorVisualComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Offset value
	Offset = FVector(100.f);
}


// Called when the game starts
void UActorVisualComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorVisualComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//----------------------------------------------------------------------------------------------------------------------
// Update Mesh Offset C++ implementation
//----------------------------------------------------------------------------------------------------------------------
void UActorVisualComponent::UpdateMeshOffset_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Update Mesh Offset C++ implementation"));

	AddLocalOffset(Offset);
}

