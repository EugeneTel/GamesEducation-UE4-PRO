// Fill out your copyright notice in the Description page of Project Settings.


#include "GECharacterAnimInstance.h"
#include "GamesEducationCharacter.h"
#include "GameFramework/PawnMovementComponent.h"


void UGECharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // cache the pawn
    Owner = Cast<AGamesEducationCharacter>(TryGetPawnOwner());
    
}

void UGECharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!Owner)
        return;

    Speed = Owner->GetVelocity().Size();
    bIsMoving = Speed > 0 ? true : false;
    bIsInAir = Owner->GetMovementComponent()->IsFalling();
}
