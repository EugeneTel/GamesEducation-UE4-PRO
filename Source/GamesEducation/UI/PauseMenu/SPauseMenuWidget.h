// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class AGamesEducationHUD;

/**
 * 
 */
class GAMESEDUCATION_API SPauseMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPauseMenuWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<AGamesEducationHUD>, OwnerHUDArg);
	
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	

	/** Play button action */
	FReply OnPlayClicked() const;

	/** Quit button action */
	FReply OnQuitClicked() const;

private:
	
	TWeakObjectPtr<AGamesEducationHUD> OwnerHUD;
};
