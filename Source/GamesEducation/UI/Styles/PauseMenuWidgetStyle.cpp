// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidgetStyle.h"

#include "Styling/CoreStyle.h"

FPauseMenuStyle::FPauseMenuStyle()
{
	BackgroundImage.TintColor = *(new FSlateColor(FLinearColor::Gray));

	ContentPadding = FMargin(300.f, 300.f);
	ButtonPadding = FMargin(10.f);

	ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleTextStyle.Size = 60.f;
}

FPauseMenuStyle::~FPauseMenuStyle()
{
}

const FName FPauseMenuStyle::TypeName(TEXT("FPauseMenuStyle"));

const FPauseMenuStyle& FPauseMenuStyle::GetDefault()
{
	static FPauseMenuStyle Default;
	return Default;
}

void FPauseMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

