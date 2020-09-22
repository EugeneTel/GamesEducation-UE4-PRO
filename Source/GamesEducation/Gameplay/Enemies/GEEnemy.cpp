// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGEEnemy::AGEEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGEEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGEEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGEEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AGEEnemy::IsAlive() const
{
	return MovementStatus != EEnemyMovementStatus::EMS_Dead;
}

