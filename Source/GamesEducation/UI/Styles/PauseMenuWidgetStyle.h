// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"

#include "PauseMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct GAMESEDUCATION_API FPauseMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FPauseMenuStyle();
	virtual ~FPauseMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FPauseMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere)
	FSlateBrush BackgroundImage;

	UPROPERTY(EditAnywhere)
	FMargin ContentPadding;

	UPROPERTY(EditAnywhere)
	FMargin ButtonPadding;

	UPROPERTY(EditAnywhere)
	FSlateFontInfo ButtonTextStyle;

	UPROPERTY(EditAnywhere)
	FSlateFontInfo TitleTextStyle;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UPauseMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FPauseMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
