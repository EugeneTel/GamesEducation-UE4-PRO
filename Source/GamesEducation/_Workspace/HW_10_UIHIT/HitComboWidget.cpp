﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComboWidget.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"
#include "GamesEducation/GamesEducationCharacter.h"

void UHitComboWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Subscribe to the Character Hit Enemy event
    AGamesEducationCharacter::NotifyHitEnemy.AddUObject(this, &UHitComboWidget::OnEnemyHit);

    // Subscribe to the Character Hit Enemy event
    AGamesEducationCharacter::NotifyShootMiss.AddUObject(this, &UHitComboWidget::OnShootMiss);

    StoreWidgetAnimations();

    ComboFadeAnimation = GetAnimationByName(TEXT("ComboFade"));
    ComboShakeAnimation = GetAnimationByName(TEXT("ComboShake"));

    ResetCombo();
}

void UHitComboWidget::UpdateComboCount(int32 Value)
{
    // only update if more than one hit
    if (!TXTCombo || Value <= 1)
        return;

    // make visible
    if (TXTCombo->Visibility == ESlateVisibility::Hidden)
    {
        TXTCombo->SetVisibility(ESlateVisibility::Visible);
    }
    TXTCombo->SetText(FText::FromString((FString::FromInt(Value) + "x")));

    // play animations
    if (ComboShakeAnimation)
    {
        PlayAnimation(ComboShakeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
    }
    if (ComboFadeAnimation)
    {
        PlayAnimation(ComboFadeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
    }

    // Update other components

    if (TXTComboLeft->Visibility == ESlateVisibility::Hidden)
    {
        TXTComboLeft->SetVisibility(ESlateVisibility::Visible);
    }

    TXTComboLeft->SetText(FText::FromString((FString::FromInt(Value - 1) + "x")));

    if (TXTComboRight->Visibility == ESlateVisibility::Hidden)
    {
        TXTComboRight->SetVisibility(ESlateVisibility::Visible);
    }
    TXTComboRight->SetText(FText::FromString((FString::FromInt(Value + 1) + "x")));
}

void UHitComboWidget::ResetCombo() const
{
   // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, __FUNCTION__);

    if (TXTCombo)
    {
        TXTCombo->SetVisibility(ESlateVisibility::Hidden);
    }

    if (TXTComboLeft)
    {
        TXTComboLeft->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (TXTComboRight)
    {
        TXTComboRight->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UHitComboWidget::StoreWidgetAnimations()
{
    AnimationsMap.Empty();

    UProperty* Prop = GetClass()->PropertyLink;

    // check each property of this class
    while (Prop)
    {
        // only evaluate object properties, skip rest
        if (Prop->GetClass() == UObjectProperty::StaticClass())
        {
            UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

            if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
            {
                UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

                // only get back properties that are of type widget animation
                UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Obj);

                // if casting worked update map with new animation
                if (WidgetAnimation && WidgetAnimation->MovieScene)
                {
                    FName AnimName = WidgetAnimation->MovieScene->GetFName();
                    GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, AnimName.ToString());
                    AnimationsMap.Add(AnimName, WidgetAnimation);
                }
            }
        }

        Prop = Prop->PropertyLinkNext;
    }
}

UWidgetAnimation* UHitComboWidget::GetAnimationByName(const FName AnimationName) const
{
    UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);
    if (WidgetAnimation)
    {
        return *WidgetAnimation;
    }
    return nullptr;
}

void UHitComboWidget::OnEnemyHit(AActor* HitActor)
{
    HitCount++;
    UpdateComboCount(HitCount);
}

void UHitComboWidget::OnShootMiss()
{
    HitCount = 0;
    ResetCombo();
}
