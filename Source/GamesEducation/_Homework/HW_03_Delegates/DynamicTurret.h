// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

#include "Log.h"
#include "GameFramework/Character.h"

#include "DynamicTurret.generated.h"


/**
* Declare OnTurretHit Delegate
* 
* @return FVector - Offset for the Turret Movement
*/
DECLARE_DELEGATE_RetVal_OneParam(FVector, FOnDamage, class ADynamicTurret*)


UCLASS()
class GAMESEDUCATION_API ADynamicTurret : public AActor
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(ADynamicTurret, FOnDeath, ADynamicTurret*)


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
	void SetupMovementRoute() const;

	/** The Turret Looks on the Player */
	UFUNCTION()
	void LookOnTarget() const;

public:

	/** On Damage Delegate */
	FOnDamage OnDamage;

	/** On Death Delegate */
	FOnDeath OnDeath;

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

	/** On Turret Hit */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	/** Takes damage */
	UFUNCTION()
	void Damage(AActor* OtherActor);

	/** The Turret Death */
	UFUNCTION()
	void Death();
};
