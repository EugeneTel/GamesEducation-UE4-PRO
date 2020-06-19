// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CanvasItem.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "_Homework/HW_05_UMG_C/PlayerStateWidget.h"

#include "GamesEducationHUD.generated.h"

class UUserWidget;
class UTexture2D;
class ADynamicTurret;

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

	/** Array of information strings to render (Reload, Kill enemy etc) */
	TArray<FCanvasTextItem> InfoItems;

	/** How long the Info text will be on the screen in seconds */
	float InfoDisplayTime;

	/** Large font - used for ammo display etc. */
	UPROPERTY()
	UFont* BigFont;

	/** Normal font - used for death messages and such. */
	UPROPERTY()
    UFont* NormalFont;

	/** Lighter HUD color. */
	FColor HUDLight;

	/** Darker HUD color. */
	FColor HUDDark;

	/** UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/** FontRenderInfo enabling casting shadow.s */
	FFontRenderInfo ShadowedFont;

	/** Minimal HUD scale for ScaleUI */
	float MinHudScale;

	/** When we got last notice about out of ammo. */
	float NoAmmoNotifyTime;

	/** When we got last notice about enemy kill. */
	float EnemyKillTime;

	virtual void PostInitializeComponents() override;

	/**
	* Render the info messages.
	*
	* @param YOffset	YOffset from top of canvas to start drawing the messages
	* @param TextScale	Text scale factor
	*
	* @returns The next Y position to draw any further strings
	*/
	float ShowInfoItems(float YOffset, float TextScale);

	/**
	* Add information string that will be displayed on the hud. They are added as required and rendered together to prevent overlaps 
	* 
	* @param InInfoString	InInfoString
	*/
	void AddInfoString(const FCanvasTextItem InInfoString);

	/**
	 * Draw Crosshair on HUD
	 */
	void DrawCrosshair();

	/**
	 * Draw Info Messages
	 */
	void DrawInfo();

	/**
	 * Draw Enemy Kill on HUD
	 */
	void DrawEnemyKill();

	/**
	* Draw No Ammo message on HUD
	*/
	void DrawNoAmmo();

	/**
	 * Event OnEnemyKill
	 */
	void OnEnemyKill(ADynamicTurret* Enemy);

	/**
	 * Event OnNoAmmo
	 */
	void OnNoAmmo();
	
private:
	/** Crosshair asset pointer */
	UTexture2D* CrosshairTex;

	/** Player State widget */
	UPROPERTY()
	UUserWidget* PlayerStateWidget;

	/** Player State Widget Class */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerStateWidget> PlayerStateWidgetClass;

	/** Create custom widgets */
	UFUNCTION()
	void CreateCustomWidget();

};

