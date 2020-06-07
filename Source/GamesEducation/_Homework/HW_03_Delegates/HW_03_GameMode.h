// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicTurret.h"
#include "GameFramework/GameModeBase.h"

#include "Log.h"
#include "HW_03_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API AHW_03_GameMode : public AGameModeBase
{
	GENERATED_BODY()


public:

	/** Player Score */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PlayerScore = 0;

	/** Register a Turret in the Game */
	UFUNCTION(BlueprintCallable)
	void AddTurret(ADynamicTurret* Turret);

	/** On Turret Damage Delegate function */
	UFUNCTION()
	FVector TurretDamage(ADynamicTurret* Turret);

	/** On turret Death Delegate Function */
	UFUNCTION()
	void TurretDeath(ADynamicTurret* Turret);

	/** Add Player Score */
	UFUNCTION()
	void AddPlayerScore(int32 Amount);
};
