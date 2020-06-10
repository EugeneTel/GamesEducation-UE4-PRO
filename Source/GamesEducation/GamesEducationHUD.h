// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "_Homework/HW_05_UMG_C/PlayerStateWidget.h"

#include "GamesEducationHUD.generated.h"

UCLASS()
class AGamesEducationHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGamesEducationHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	void BeginPlay() override;
protected:
	virtual void PostInitializeComponents() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	/** Player State widget */
	UPROPERTY()
	class UUserWidget* PlayerStateWidget;

	/** Player State Widget Class */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerStateWidget> PlayerStateWidgetClass;

	/** Create custorm widgets */
	UFUNCTION()
	void CreateCustomWidget();

};

