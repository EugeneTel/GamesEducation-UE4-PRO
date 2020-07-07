// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamesEducationHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "GamesEducation/_Homework/HW_03_Delegates/DynamicTurret.h"
#include "GamesEducation/GamesEducationCharacter.h"
#include "Log.h"

AGamesEducationHUD::AGamesEducationHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	// Load Fonts
	static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/FirstPerson/Fonts/Roboto51"));
	static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/FirstPerson/Fonts/Roboto18"));
	BigFont = BigFontOb.Object;
	NormalFont = NormalFontOb.Object;

	// HUD
	HUDLight = FColor(175,202,213,255);
	HUDDark = FColor(110,124,131,255);
	ShadowedFont.bEnableShadow = true;
	MinHudScale = 0.5f;
	InfoDisplayTime = 2.f;
}

void AGamesEducationHUD::DrawInfo()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float MessageOffset = (Canvas->ClipY / 2.0) * ScaleUI;
	
	// Empty the info items array
	InfoItems.Empty();

	// Draw Enemy Kill text if needed
	if (EnemyKillTime && (EnemyKillTime + InfoDisplayTime) >= CurrentTime)
	{
		DrawEnemyKill();
	}

	// Draw NoAmmo text if needed
	if (NoAmmoNotifyTime && (NoAmmoNotifyTime + InfoDisplayTime) >= CurrentTime)
	{
		DrawNoAmmo();
	}
	
	ShowInfoItems(MessageOffset, 1.0f);
}

void AGamesEducationHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas == nullptr)
	{
		return;
	}

	// Prepare ScaleUI
	ScaleUI = Canvas->ClipY / 1080.0f;

	DrawCrosshair();

	// Draw Info Messages
	DrawInfo();
}

void AGamesEducationHUD::BeginPlay()
{
	Super::BeginPlay();

	// EnemyKill subscription
	AGamesEducationCharacter::NotifyEnemyKill.AddUObject(this, &AGamesEducationHUD::OnEnemyKill);

	// NoAmmo subscription
	AGamesEducationCharacter::NotifyNoAmmo.AddUObject(this, &AGamesEducationHUD::OnNoAmmo);

	CreateCustomWidgets();
}

void AGamesEducationHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGamesEducationHUD::DrawCrosshair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X), (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AGamesEducationHUD::DrawEnemyKill()
{	
	float TextScale = 1.0f;
	const FString KillText("Killed");
	FCanvasTextItem TextItem( FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow( FLinearColor::Black );
	TextItem.Text = FText::FromString(KillText);
	TextItem.Scale = FVector2D( TextScale * ScaleUI, TextScale * ScaleUI );
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(HUDLight);
	AddInfoString(TextItem);
}

void AGamesEducationHUD::DrawNoAmmo()
{
	float TextScale = 0.7f;
	const FString KillText("No Ammo");
	FCanvasTextItem TextItem( FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow( FLinearColor::Black );
	TextItem.Text = FText::FromString(KillText);
	TextItem.Scale = FVector2D( TextScale * ScaleUI, TextScale * ScaleUI );
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(FColor::Red);
	AddInfoString(TextItem);
}

void AGamesEducationHUD::OnEnemyKill(ADynamicTurret* Enemy)
{
	EnemyKillTime = GetWorld()->GetTimeSeconds();
}

void AGamesEducationHUD::OnNoAmmo()
{
	NoAmmoNotifyTime = GetWorld()->GetTimeSeconds();
}

float AGamesEducationHUD::ShowInfoItems(float YOffset, float TextScale)
{
	float Y = YOffset;
	float CanvasCentre = Canvas->ClipX / 2.0f;

	for (int32 iItem = 0; iItem < InfoItems.Num() ; iItem++)
	{
		float X = 0.0f;
		float SizeX, SizeY; 
		Canvas->StrLen(InfoItems[iItem].Font, InfoItems[iItem].Text.ToString(), SizeX, SizeY);
		X = CanvasCentre - ( SizeX * InfoItems[iItem].Scale.X)/2.0f;
		Canvas->DrawItem(InfoItems[iItem], X, Y);
		Y += SizeY * InfoItems[iItem].Scale.Y;
	}
	return Y;
}

void AGamesEducationHUD::AddInfoString(const FCanvasTextItem InInfoString)
{
	InfoItems.Add(InInfoString);
}

void AGamesEducationHUD::CreateCustomWidgets()
{
	// Create Main Menu Widget
	if (!MainMenuWidget && IdToMenu[EMenus::E_MainMenu])
	{
		MainMenuWidget = CreateWidget(GetWorld(), IdToMenu[EMenus::E_MainMenu]);
		MainMenuWidget->AddToViewport();
	}
	
	// Create Player State Widget
	if (!PlayerStateWidget && PlayerStateWidgetClass)
	{
		PlayerStateWidget = CreateWidget(GetWorld(), PlayerStateWidgetClass);
		PlayerStateWidget->AddToViewport();
	}
}
