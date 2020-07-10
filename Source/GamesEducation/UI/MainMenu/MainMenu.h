// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


#include "MainMenu.generated.h"

class UVerticalBox;
class UBaseButton;
class MainMenuHandler;

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
    UPROPERTY()
    TMap<int32, UBaseButton*> _MainMenuBtns;

    TSharedPtr<MainMenuHandler> _InputHandler;

    int32 _CurrentSelectedItem;

    int32 _PrevSelectedItem;

    int32 _MaxItems;

protected:
    void NativeDestruct() override;

    void NativePreConstruct() override;
public:

    UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
    UVerticalBox* MainMenuContainer;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UBaseButton> BtnTemplate;

    UPROPERTY(meta = (BindWidgetOptional))
    UImage* BackgroundImage;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* TitleText;

    void NativeConstruct() override;

    void NextItem();

    void PrevItem();

    void SelectItem(int32 Index);

    void UnSelectItem(int32 Index);
    
};
