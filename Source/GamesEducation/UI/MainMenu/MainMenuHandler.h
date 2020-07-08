// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/IInputProcessor.h"

class UUserWidget;

/**
 * 
 */
class GAMESEDUCATION_API MainMenuHandler : public IInputProcessor
{
public:
	explicit MainMenuHandler(UUserWidget* MainMenu);
	~MainMenuHandler();

	void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

	bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
private:

	UUserWidget* MainMenuWidget;
	
};
