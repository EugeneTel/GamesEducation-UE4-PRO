// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GamesEducationCharacter.generated.h"

class UInputComponent;
class ADynamicTurret;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGamesEducationCharacterUpdateAmmo, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGamesEducationCharacterUpdateScore, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGamesEducationCharacterEnemyKill, ADynamicTurret*);
DECLARE_MULTICAST_DELEGATE(FOnGamesEducationCharacterNoAmmo);

UCLASS(config=Game)
class AGamesEducationCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AGamesEducationCharacter();

protected:
	virtual void BeginPlay();

public:

	/** Global notification when a character updates ammo. Needed for HUD */
	GAMESEDUCATION_API static FOnGamesEducationCharacterUpdateAmmo NotifyUpdateAmmo;

	/** Global notification when a character score is updated. Needed for HUD */
	GAMESEDUCATION_API static FOnGamesEducationCharacterUpdateAmmo NotifyUpdateScore;

	/** Global notification when a character killed an enemy. Needed for HUD */
	GAMESEDUCATION_API static FOnGamesEducationCharacterEnemyKill NotifyEnemyKill;

	/** Global notification when a character has no ammo. Needed for HUD */
	GAMESEDUCATION_API static FOnGamesEducationCharacterNoAmmo NotifyNoAmmo;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    uint32 bUsingMotionControllers : 1;

	/** Weapon Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UGamesEducationWeaponComponent* WeaponComponent;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Reloads the weapon */
	void OnReload();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns FP_MuzzleLocation subobject */
	FORCEINLINE class USceneComponent* GetFP_MuzzleLocation() const { return FP_MuzzleLocation; }

public:

	/** Time Control Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
	class UTimeControlComponent* TimeControlComp;

};

