// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseMenuWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "GamesEducation/GamesEducationHUD.h"
#include "GamesEducation/UI/Styles/GamesEducationCoreStyle.h"
#include "GamesEducation/UI/Styles/PauseMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "PauseMenu"

void SPauseMenuWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUDArg;

	bCanSupportFocus = true;

	// Setup styling
	const FPauseMenuStyle& Style = GamesEducationCoreStyle::Get().GetWidgetStyle<FPauseMenuStyle>("PauseMenuStyleAsset");
	
	const FSlateBrush BackgroundImage = Style.BackgroundImage;
	const FMargin ContentPadding = Style.ContentPadding;
	const FMargin ButtonPadding = Style.ButtonPadding;
	const FSlateFontInfo ButtonTextStyle = Style.ButtonTextStyle;
	const FSlateFontInfo TitleTextStyle = Style.TitleTextStyle;

	// Setup texts
	const FText TitleText = LOCTEXT("GameTitle", "GamesEducation");
	const FText PlayText = LOCTEXT("PlayGame", "Play");
	const FText SettingsText = LOCTEXT("Settings", "Settings");
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&BackgroundImage)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)

			// Title Text
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(TitleTextStyle)
				.Text(TitleText)
				.Justification(ETextJustify::Center)
			]

			// Play button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SPauseMenuWidget::OnPlayClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(PlayText)
					.Justification(ETextJustify::Center)
				]
			]

			// Settings button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
			    SNew(SButton)
			    [
			        SNew(STextBlock)
			        .Font(ButtonTextStyle)
			        .Text(SettingsText)
			        .Justification(ETextJustify::Center)
			    ]
			]

			// Quit button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
			    SNew(SButton)
			    .OnClicked(this, &SPauseMenuWidget::OnQuitClicked)
			    [
			        SNew(STextBlock)
			        .Font(ButtonTextStyle)
			        .Text(QuitText)
			        .Justification(ETextJustify::Center)
			    ]
			]
			
		]
	];
	
}

FReply SPauseMenuWidget::OnPlayClicked() const
{
	if (OwnerHUD.IsValid())
	{
		OwnerHUD->RemovePauseMenu();
	}
	
	return FReply::Handled();
}

FReply SPauseMenuWidget::OnQuitClicked() const
{
	if (OwnerHUD.IsValid())
	{
		if (APlayerController* PC = OwnerHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}
	
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
