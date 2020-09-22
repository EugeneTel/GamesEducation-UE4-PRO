// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GEMovingEnemy.h"
#include "Animation/AnimInstance.h"
#include "GEMovingEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UGEMovingEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite)
    AGEMovingEnemy* Owner;
	
    UPROPERTY(BlueprintReadWrite)
    bool bIsMoving;
	
    UPROPERTY(BlueprintReadWrite)
    bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsAttacking;

    UPROPERTY(BlueprintReadWrite)
    float Speed;

    virtual void NativeInitializeAnimation() override;
	
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
