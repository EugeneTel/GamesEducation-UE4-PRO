// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamesEducation.h"
#include "Modules/ModuleManager.h"
#include "UI/Styles/GamesEducationCoreStyle.h"

void FGamesEducationModule::StartupModule()
{
    FDefaultGameModuleImpl::StartupModule();

    GamesEducationCoreStyle::Initialize();
}

void FGamesEducationModule::ShutdownModule()
{
    GamesEducationCoreStyle::Shutdown();

    FDefaultGameModuleImpl::ShutdownModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE( FGamesEducationModule, GamesEducation, "GamesEducation" );
