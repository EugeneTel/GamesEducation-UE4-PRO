// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "GEEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus : uint8
{
	EMS_Idle UMETA(DispayName = "Idle"),
    EMS_MoveToTarget UMETA(DisplayName = "MoveToTarget"),
    EMS_Attacking UMETA(DisplayName = "Attacking"),
    EMS_Dead UMETA(DisplayName = "Dead"),

    EMS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class GAMESEDUCATION_API AGEEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// USkeletalMeshComponent* Mesh;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	// UMovementComponent* PawnMovement;

public:

	/** Enemy Status */
	UPROPERTY(BlueprintReadWrite)
	EEnemyMovementStatus MovementStatus;

	/** Set debug mode for the enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugMode;
	
	// Sets default values for this pawn's properties
	AGEEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Checks is enemy alive */
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

};
