// Fill out your copyright notice in the Description page of Project Settings.

#include "GEPlayerController.h"

#include "GamesEducationHUD.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AGEPlayerController::BeginPlay()
{
    Super::BeginPlay();

    CurrentPlayerName = "Player_" + FString::FromInt(FMath::RandHelper(10000));
}

void AGEPlayerController::ReceiveMessage_Implementation(const FText& Message)
{
    AGamesEducationHUD* HUD = Cast<AGamesEducationHUD>(GetHUD());
    if (HUD)
    {
        HUD->AddMessageToChatWindow(Message);
    }
}

void AGEPlayerController::SendChatMessage_Implementation(const FText& Message)
{
    const FText MessageWithName = FText::Format(NSLOCTEXT("MultiplayerChat", "Message", "{0}: {1}"),
                                                FText::FromString(CurrentPlayerName), Message);

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGEPlayerController::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        AGEPlayerController* Controller = Cast<AGEPlayerController>(Actor);
        Controller->ReceiveMessage(MessageWithName);
    }
}
