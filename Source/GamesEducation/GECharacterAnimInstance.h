// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GamesEducationCharacter.h"
#include "Animation/AnimInstance.h"
#include "GECharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UGECharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	AGamesEducationCharacter* Owner;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsMoving;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsInAir;

	UPROPERTY(BlueprintReadWrite)
	float Speed;

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
