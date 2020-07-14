// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamage.h"
#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

#include "Log.h"
#include "GameFramework/Character.h"

#include "DynamicTurret.generated.h"


/**
* Declare FOnDamaged Delegate
* 
* @return FVector - Offset for the Turret Movement
*/
DECLARE_DELEGATE_RetVal_OneParam(FVector, FOnDamaged, class ADynamicTurret*)

/** Declare FOnDeath Delegate */
DECLARE_EVENT_OneParam(ADynamicTurret, FOnDeath, ADynamicTurret*)

UCLASS()
class GAMESEDUCATION_API ADynamicTurret : public AActor, public IIDamage
{
	GENERATED_BODY()


public:	
    // Sets default values for this actor's properties
    ADynamicTurret();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Instance of the Current player */
	UPROPERTY(BlueprintReadOnly)
	ACharacter* CurrentPlayer;

	/** Is the Turret Alive */
	UPROPERTY(BlueprintReadWrite)
	bool bAlive;

	/** Setup The Turret Route based on the Spline points */ 
	UFUNCTION()
	virtual void SetupMovementRoute() const;

	/** The Turret Looks on the Player */
	UFUNCTION()
	void LookOnTarget() const;

public:

	/** On Damage Received Delegate */
	FOnDamageReceived OnDamageReceivedEvent;
	
	/** On Damage Delegate */
	FOnDamaged OnDamagedEvent;

	/** On Death Delegate */
	FOnDeath OnDeathEvent;

	/** Collisions */
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp;

	/** Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	/** Spline Component */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* SplineComp;

	/** Movement Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInterpToMovementComponent* MovementComp;

	/** The Turret Health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float Health;

	/** The number of points for the turret killing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	int32 Score;

	/** Delegate method */ 
	virtual FOnDamageReceived& OnDamageReceived() override;

	/** Subscribed to the Delegate OnDamageReceived */
	void ApplyDamage(float Damage);

	/** The Turret Death */
	UFUNCTION()
	void Death();
};
