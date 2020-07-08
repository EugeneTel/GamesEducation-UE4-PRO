// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHandler.h"

#include "MainMenu.h"
#include "Input/Events.h"

MainMenuHandler::MainMenuHandler(UUserWidget* MainMenu)
{
    MainMenuWidget = MainMenu;
}

MainMenuHandler::~MainMenuHandler()
{
}

void MainMenuHandler::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
}

bool MainMenuHandler::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("KeyUp Handeled: %s"), *InKeyEvent.GetKey().ToString());
    
    if (InKeyEvent.GetKey() == EKeys::W)
    {
        Cast<UMainMenu>(MainMenuWidget)->PrevItem();
    } else if (InKeyEvent.GetKey() == EKeys::S)
    {
        Cast<UMainMenu>(MainMenuWidget)->NextItem();
    }
    
    return true;
}
