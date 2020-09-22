// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ChatMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UChatMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMessageText(FText NewText) const;

protected:

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* MessageText;
	
};
