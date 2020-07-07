// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamesEducation/UI/IFocusable.h"

#include "BaseButton.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UBaseButton : public UUserWidget, public IIFocusable
{
    GENERATED_BODY()

private:
    int32 _Index;
    bool _IsInFocus;

public:

    UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
    UButton* CurrentBtn;

    void NativeConstruct() override;
    int32 GetIndex() override;
    void SetIndex(int32 Index) override;
    bool IsInFocus() override;
    void Focus() override;
    void UnFocus() override;

    UFUNCTION( )
    void OnButtonReleased() override;
};
