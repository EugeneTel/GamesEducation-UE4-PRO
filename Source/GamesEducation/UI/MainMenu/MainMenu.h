// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainMenu.generated.h"

class UVerticalBox;
class UBaseButton;

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
    UPROPERTY()
    TArray<UBaseButton*> _MainMenuBtns;
    
public:

    void NativeConstruct() override;

    FReply NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent) override;


    UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
    UVerticalBox* MainMenuContainer;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UBaseButton> BtnTemplate;
};
