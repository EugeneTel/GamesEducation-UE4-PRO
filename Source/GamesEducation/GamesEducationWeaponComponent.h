// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamesEducationCharacter.h"
#include "Components/ActorComponent.h"

#include "Log.h"
#include "GamesEducationWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESEDUCATION_API UGamesEducationWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGamesEducationWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Weapon Owner Character */
	UPROPERTY()
	AGamesEducationCharacter* WeaponOwner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Fire the Weapon */
	UFUNCTION(BlueprintCallable)
	void Fire();

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
    TSubclassOf<class AGamesEducationProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimMontage* FireAnimation;

//----------------------------------------------------------------------------------------------------------------------
// File System
//----------------------------------------------------------------------------------------------------------------------

	/** Save Data to the File */
	UFUNCTION(BlueprintCallable)
	bool SaveToFile(FString FileName, FString Data);

	/** Load Data from the File */ 
	UFUNCTION(BlueprintCallable)
	bool LoadFromFile(FString FileName, FString& OutData);

	
//----------------------------------------------------------------------------------------------------------------------
// Ammo
//----------------------------------------------------------------------------------------------------------------------
	
	/** File name for saving the ammo data */
	UPROPERTY(EditDefaultsOnly, Category=Ammo)
	FName SaveAmmoFileName;

	/** Number of Ammo */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Ammo)
	int32 Ammo;

	/** Maximal number of Ammo */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Ammo)
	int32 MaxAmmo;

	/** Use ammo for firing */
	UFUNCTION(BlueprintCallable, Category=Ammo)
	void UseAmmo();

	/** Does the player has ammo */
	UFUNCTION(BlueprintCallable, Category=Ammo)
	bool HasAmmo() const;

	/** Adding ammo to the player */
	UFUNCTION(BlueprintCallable, Category=Ammo)
	void AddAmmo(int32 Amount);

	/** Init ammo from the saved file */
	UFUNCTION(BlueprintCallable, Category=Ammo)
	void InitAmmo();

	/** Reload the Ammo*/
	UFUNCTION(BlueprintCallable, Category=Ammo)
	void Reload();
};
