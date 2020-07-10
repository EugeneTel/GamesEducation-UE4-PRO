// Fill out your copyright notice in the Description page of Project Settings.


#include "GamesEducationCoreStyle.h"

#include "Slate/SlateGameResources.h"

TSharedPtr<ISlateStyle> GamesEducationCoreStyle::StylePtr = nullptr;


TSharedPtr<ISlateStyle> GamesEducationCoreStyle::CreateStyle()
{
    TSharedPtr<ISlateStyle> Style = FSlateGameResources::New("GamesEducationCoreStyle", "/Game/GamesEducation/UI/Styles", "/Game/GamesEducation/UI/Styles");

    return Style;
}

void GamesEducationCoreStyle::Initialize()
{
    if (!StylePtr.IsValid())
    {
        StylePtr = CreateStyle();
        FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
    }
}

void GamesEducationCoreStyle::Shutdown()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
    ensure(StylePtr.IsUnique());
    StylePtr.Reset();
}

const ISlateStyle& GamesEducationCoreStyle::Get()
{
    return *StylePtr;
}
