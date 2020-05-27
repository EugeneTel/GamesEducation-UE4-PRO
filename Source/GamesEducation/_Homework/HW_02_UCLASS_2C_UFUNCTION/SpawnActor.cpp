// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "ActorBehaviorComponent.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Visual component
	VisualComponent = CreateDefaultSubobject<UActorVisualComponent>(TEXT("VisualComponent"));
	SetRootComponent(VisualComponent);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

	CreateBehaviorComponent();
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
// Create Behavior Component
//----------------------------------------------------------------------------------------------------------------------
void ASpawnActor::CreateBehaviorComponent()
{
	if (BehaviorComponentClass)
	{
		BehaviorComponent = NewObject<UActorBehaviorComponent>(this, BehaviorComponentClass);
		BehaviorComponent->SetupAttachment(GetRootComponent());
		BehaviorComponent->RegisterComponent();
	}
}

