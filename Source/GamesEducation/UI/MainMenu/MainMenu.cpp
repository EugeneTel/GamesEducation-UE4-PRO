// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/VerticalBox.h"
#include "BaseButton.h"
#include "MainMenuHandler.h"
#include "Framework/Application/SlateApplication.h"
#include "GamesEducation/UI/Styles/GamesEducationCoreStyle.h"
#include "GamesEducation/UI/Styles/MenuWidgetStyle.h"

void UMainMenu::NativeConstruct()
{
    _MaxItems = 3;
    _CurrentSelectedItem = -1;

    // Create a list of Buttons
    for (int32 i = 0; i < _MaxItems; ++i)
    {
        UBaseButton* Btn = CreateWidget<UBaseButton>(this, BtnTemplate);
        Btn->SetIndex(i);
        Btn->SetColorAndOpacity(FLinearColor::Gray);
        Btn->bIsFocusable = true;
        _MainMenuBtns.Add(i, Btn);
        MainMenuContainer->AddChild(Btn);
    }

    SelectItem(0);

    // Create and register MainMenuHandler
    _InputHandler = MakeShareable(new MainMenuHandler(this));
    FSlateApplication::Get().RegisterInputPreProcessor(_InputHandler);
}

void UMainMenu::NativeDestruct()
{
    Super::NativeDestruct();

    FSlateApplication::Get().UnregisterInputPreProcessor(_InputHandler);
}

void UMainMenu::NativePreConstruct()
{
    Super::NativePreConstruct();

    const FMenuStyle& Style = GamesEducationCoreStyle::Get().GetWidgetStyle<FMenuStyle>("MainMenuStyleAsset");
    
    if (BackgroundImage)
    {
        BackgroundImage->SetBrush(Style.BackgroundImage);
    }
    
    if (TitleText)
    {
        TitleText->SetFont(Style.TitleFont);
    }
}

void UMainMenu::NextItem()
{
    int32 const NewItemIndex = FMath::Min(_CurrentSelectedItem + 1, _MaxItems - 1);

    SelectItem(NewItemIndex);
}

void UMainMenu::PrevItem()
{
    int32 const NewItemIndex = FMath::Max(_CurrentSelectedItem - 1, 0);

    SelectItem(NewItemIndex);
}

void UMainMenu::SelectItem(int32 Index)
{
    if (!_MainMenuBtns.Find(Index) || Index == _CurrentSelectedItem)
        return;

    UnSelectItem(_CurrentSelectedItem);
    _MainMenuBtns[Index]->SetFocus();
    _MainMenuBtns[Index]->SetColorAndOpacity(FLinearColor::Green);
    _CurrentSelectedItem = Index;
    
}

void UMainMenu::UnSelectItem(int32 Index)
{
    if (!_MainMenuBtns.Find(Index))
        return;
    
    _MainMenuBtns[Index]->UnFocus();
    _MainMenuBtns[Index]->SetColorAndOpacity(FLinearColor::Gray);
}


