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

	// Create Behavior Component as a SimpleRotatingComponent
	BehaviorComponent = CreateDefaultSubobject<USimpleRotatingComponent>(TEXT("BehaviorComponent"));
	BehaviorComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

