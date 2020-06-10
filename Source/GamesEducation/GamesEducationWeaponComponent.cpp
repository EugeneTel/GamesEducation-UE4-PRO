// Fill out your copyright notice in the Description page of Project Settings.


#include "GamesEducationWeaponComponent.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "GamesEducationProjectile.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UGamesEducationWeaponComponent::UGamesEducationWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Setup Defaults
	MaxAmmo = 10;
}


// Called when the game starts
void UGamesEducationWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponOwner = Cast<AGamesEducationCharacter>(GetOwner());
	if (!WeaponOwner)
		UE_LOG(LogTemp, Error, TEXT("Weapon Owner is not defined!"));
}


// Called every frame
void UGamesEducationWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGamesEducationWeaponComponent::Fire()
{
	if (!HasAmmo())
	{
		ULog::Error("No Ammo!!!", LO_Both);
		return;
	}
	
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = WeaponOwner->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((WeaponOwner->GetFP_MuzzleLocation() != nullptr) ? WeaponOwner->GetFP_MuzzleLocation()->GetComponentLocation() : WeaponOwner->GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AGamesEducationProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			// Use 1 bullet
			UseAmmo();
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, WeaponOwner->GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = WeaponOwner->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
// File System
//----------------------------------------------------------------------------------------------------------------------

bool UGamesEducationWeaponComponent::SaveToFile(FString FileName, FString Data)
{
	if (FileName.IsEmpty())
	{
		ULog::Error("FileName can't be Empty!");
		return false;
	}
	
	FString SaveDirectory = FPaths::ProjectSavedDir();
	const FString FilePath = FPaths::Combine(SaveDirectory, FileName);

	FText FileError;
	if (FFileHelper::IsFilenameValidForSaving(FilePath, FileError))
	{
		return FFileHelper::SaveStringToFile(Data, *FilePath);
	} else
	{
		ULog::Error(FileError.ToString(), LO_Both);
	}

	return false;
}

bool UGamesEducationWeaponComponent::LoadFromFile(FString FileName, FString& OutData)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString SaveDirectory = FPaths::ProjectSavedDir();
	const FString FilePath = FPaths::Combine(SaveDirectory, FileName);

	if (PlatformFile.FileExists(*FilePath))
	{
		return FFileHelper::LoadFileToString(OutData, *FilePath);
	} else
	{
		ULog::Info("Saving Ammo file is not exist!", LO_Both);
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------
// Ammo
//----------------------------------------------------------------------------------------------------------------------

void UGamesEducationWeaponComponent::UseAmmo()
{
	Ammo -= 1;

	// Notify subscribers about updating ammo
	AGamesEducationCharacter::NotifyUpdateAmmo.Broadcast(Ammo);

	if (SaveToFile(SaveAmmoFileName.ToString(), FString::FromInt(Ammo)))
	{
		ULog::Number(Ammo, "Number of Ammo: ", "", DLNS_Decimal, LO_Both);
	} else
	{
		ULog::Error("Ammo can't be saved!", LO_Both);
	}
}

bool UGamesEducationWeaponComponent::HasAmmo() const
{
	return Ammo > 0;
}

void UGamesEducationWeaponComponent::AddAmmo(int32 Amount)
{
	Ammo += Amount;

	// Notify subscribers about updating ammo
	AGamesEducationCharacter::NotifyUpdateAmmo.Broadcast(Ammo);

	if (SaveToFile(SaveAmmoFileName.ToString(), FString::FromInt(Ammo)))
	{
		ULog::Number(Ammo, "Ammo Added Number of Ammo: ", "", DLNS_Decimal, LO_Both);
	} else
	{
		ULog::Error("Added Ammo can't be saved!", LO_Both);
	}
}

void UGamesEducationWeaponComponent::InitAmmo()
{
	FString Data;
	if (LoadFromFile(SaveAmmoFileName.ToString(), Data))
	{
		int32 SavedAmmo;
		if (FDefaultValueHelper::ParseInt(Data, SavedAmmo))
		{
			Ammo = SavedAmmo;
			ULog::Number(Ammo, "Ammo Successfully loaded: ", "", DLNS_Decimal, LO_Both);
		} else
		{
			ULog::Error("Loaded Ammo can't be parsed!", LO_Both);
		}
	} else
	{
		ULog::Error("Ammo can't be loaded!", LO_Both);
	}

	if (!Ammo)
	{
		Ammo = MaxAmmo;
	}

	// Notify subscribers about updating ammo
	AGamesEducationCharacter::NotifyUpdateAmmo.Broadcast(Ammo);
}

void UGamesEducationWeaponComponent::Reload()
{
	AddAmmo(MaxAmmo);
}

