// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API AGEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
    void SendChatMessage(const FText& Message);

	UFUNCTION(Client, Reliable)
    void ReceiveMessage(const FText& Message);

protected:
   
	FString CurrentPlayerName;
	
};
