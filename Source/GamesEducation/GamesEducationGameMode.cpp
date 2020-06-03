// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamesEducationGameMode.h"
#include "GamesEducationHUD.h"
#include "GamesEducationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamesEducationGameMode::AGamesEducationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGamesEducationHUD::StaticClass();
}
