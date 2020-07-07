// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/VerticalBox.h"
#include "BaseButton.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UMainMenu::NativeConstruct()
{
    for (int32 i = 0; i <3; ++i)
    {
        UBaseButton* Btn = CreateWidget<UBaseButton>(this, BtnTemplate);
        Btn->SetIndex(i);
        _MainMenuBtns.Add(Btn);
        MainMenuContainer->AddChild(Btn);
    }

    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer());

    bIsFocusable = true;
    this->SetKeyboardFocus();
}

FReply UMainMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("Widget pressed with key: %s"), *InKeyEvent.GetKey().ToString())
    
    return FReply::Handled();
}
