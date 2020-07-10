// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"

#include "MenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct GAMESEDUCATION_API FMenuStyle : public FSlateWidgetStyle
{
	GENERATED_BODY()

	FMenuStyle();
	virtual ~FMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMenuStyle& GetDefault();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MainMenu)
    FSlateBrush BackgroundImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MainMenu)
    FSlateFontInfo TitleFont;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
