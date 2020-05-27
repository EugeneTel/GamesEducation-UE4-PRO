// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorVisualComponent.h"
#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "SimpleRotatingComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class GAMESEDUCATION_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Visual Component - add visual representation to the Actor
	 * Can be set from Defaults and in Instance
	 * Can be read from blueprint
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Visual")
	UActorVisualComponent* VisualComponent;

	/**
	 * Actor BehaviorComponent - add custom behavior to the Actor
	 * Can be Visible Anywhere but not editable
	 * Can be read and write from a Blueprint
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Visual")
	UActorBehaviorComponent* BehaviorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<IInteractableInterface> Interact;

};
