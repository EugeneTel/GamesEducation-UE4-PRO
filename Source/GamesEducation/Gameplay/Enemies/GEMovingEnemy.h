// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEEnemy.h"
#include "Components/SphereComponent.h"
#include "GamesEducation/GamesEducationCharacter.h"
#include "UObject/ObjectMacros.h"


#include "GEMovingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API AGEMovingEnemy : public AGEEnemy
{
	GENERATED_BODY()

protected:

	/** Sphere where the Spider will react on the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* AgroSphere;

	/** Sphere where the Spider will attack the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AAIController* AIController;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bOverlappingAgroSphere;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bOverlappingCombatSphere;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGamesEducationCharacter* AgroTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGamesEducationCharacter* CombatTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat)
	UAnimMontage* CombatMontage;

	UPROPERTY(BlueprintReadOnly, Category = Animation)
	UAnimInstance* AnimInstance;

	void BeginPlay() override;
	

public:
	AGEMovingEnemy();

	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
    virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
    virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
    virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void MoveToTarget(class AGamesEducationCharacter* Target);

	UFUNCTION(BlueprintCallable)
	void StopMovementToTarget();

	UFUNCTION(BlueprintCallable)
    void AttackTarget(AGamesEducationCharacter* Target);

	UFUNCTION(BlueprintCallable)
    void StopAttacking();

	/** Calling from Anim_BP */
	UFUNCTION(BlueprintCallable)
    void AttackSectionEnd();

	/** Calling from Anim_BP */
	UFUNCTION(BlueprintCallable)
    void AttackComboEnd();

	/** Is enemy attacking the player */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAttacking() const { return bIsAttacking; }
	
};