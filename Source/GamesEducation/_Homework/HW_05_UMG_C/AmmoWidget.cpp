// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"

#include "GamesEducation/GamesEducationCharacter.h"
#include "GamesEducation/GamesEducationWeaponComponent.h"
#include "Log.h"

void UAmmoWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ULog::Info("UAmmoWidget::NativeConstruct", LO_Both);
    
    // Subscribe to the Character Update Ammo Event
    AGamesEducationCharacter::NotifyUpdateAmmo.AddUObject(this, &UAmmoWidget::OnUpdateAmmo);
}

void UAmmoWidget::OnUpdateAmmo(const int32 Ammo) const
{
    ULog::Info("UAmmoWidget::OnUpdateAmmo", LO_Both);
    
    AmmoText->SetText(FText::FromString(FString::FromInt(Ammo)));
}
