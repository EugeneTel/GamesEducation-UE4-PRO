// Fill out your copyright notice in the Description page of Project Settings.


#include "GEMovingEnemyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UGEMovingEnemyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // cache the pawn
    Owner = Cast<AGEMovingEnemy>(TryGetPawnOwner());
}

void UGEMovingEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!Owner)
        return;

    Speed = Owner->GetVelocity().Size();
    bIsMoving = Speed > 0 ? true : false;
    bIsInAir = Owner->GetMovementComponent()->IsFalling();
    bIsAttacking = Owner->IsAttacking();
}
