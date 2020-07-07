// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseButton.h"
#include "Components/Button.h"

void UBaseButton::NativeConstruct()
{
    Super::NativeConstruct();

    CurrentBtn->OnReleased.AddDynamic(this, &UBaseButton::OnButtonReleased);
}

int32 UBaseButton::GetIndex()
{
    return _Index;
}

void UBaseButton::SetIndex(int32 Index)
{
    _Index = Index;
}

bool UBaseButton::IsInFocus()
{
    return _IsInFocus;
}

void UBaseButton::Focus()
{
    _IsInFocus = true;
}

void UBaseButton::UnFocus()
{
    _IsInFocus = false;
}

void UBaseButton::OnButtonReleased()
{
    UE_LOG(LogTemp, Warning, TEXT("Button with index : %s >> released"), *FString::FromInt(_Index));
}
