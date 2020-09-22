// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"

#include "ChatWindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UChatWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void AddMessage(FText Message) const;

protected:

	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* ChatScrollBox;

	UPROPERTY(meta = (BindWidgetOptional))
	UEditableTextBox* NewMessageTextBox;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SendButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* CloseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UChatMessageWidget> MessageWidgetClass;

	UFUNCTION()
	void OnSendButtonClicked();

	UFUNCTION()
	void OnCloseButtonClicked();
	
};
