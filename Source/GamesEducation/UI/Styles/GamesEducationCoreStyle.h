// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

/**
 * 
 */
class GAMESEDUCATION_API GamesEducationCoreStyle
{
public:
    static TSharedPtr<ISlateStyle> StylePtr;
    
    static void Initialize();
    static void Shutdown();

    static const ISlateStyle& Get();

    static TSharedPtr<ISlateStyle> CreateStyle();
};
