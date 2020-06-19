// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_03_GameMode.h"

#include "Kismet/KismetMathLibrary.h"
#include "GamesEducation/GamesEducationCharacter.h"

void AHW_03_GameMode::StartPlay()
{
    Super::StartPlay();
    
    AGamesEducationCharacter::NotifyUpdateScore.Broadcast(PlayerScore);
}

//----------------------------------------------------------------------------------------------------------------------
// Register a Turret in the Game
//----------------------------------------------------------------------------------------------------------------------
void AHW_03_GameMode::AddTurret(ADynamicTurret* Turret)
{
    Turret->OnDamagedEvent.BindUFunction(this, "TurretDamage");
    Turret->OnDeathEvent.AddUFunction(this, "TurretDeath");
}

//----------------------------------------------------------------------------------------------------------------------
// On Turret Damage Delegate function
//----------------------------------------------------------------------------------------------------------------------
FVector AHW_03_GameMode::TurretDamage(ADynamicTurret* Turret)
{
    return UKismetMathLibrary::RandomPointInBoundingBox(FVector(100.f), FVector(200.f));
}

//----------------------------------------------------------------------------------------------------------------------
// On turret Death Delegate Function
//----------------------------------------------------------------------------------------------------------------------
void AHW_03_GameMode::TurretDeath(ADynamicTurret* Turret)
{
    AddPlayerScore(Turret->Score);

    // Notify subscribers about killing a turret
    AGamesEducationCharacter::NotifyEnemyKill.Broadcast(Turret);
}

//----------------------------------------------------------------------------------------------------------------------
// Add Player Score
//----------------------------------------------------------------------------------------------------------------------
void AHW_03_GameMode::AddPlayerScore(const int32 Amount)
{
    PlayerScore += Amount;

    // Notify subscribers about updating Score
    AGamesEducationCharacter::NotifyUpdateScore.Broadcast(PlayerScore);
}
