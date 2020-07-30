// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "ActorBehaviorComponent.generated.h"

/**
 * Abstract Component for other actor behavior components implementation
 * Can be spawned by a Blueprint, belongs to ClassGroup "Behavior"
 * Can't be Blueprint implemented
 */
UCLASS( Abstract, ClassGroup=(Behavior), meta=(BlueprintSpawnableComponent) )
class GAMESEDUCATION_API UActorBehaviorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorBehaviorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Enable The Component Behavior
	 */
	FORCEINLINE void Enable() { IsEnabled = true; };

	/**
	 * Disable The Component Behavior
	 * Can be called from Blueprint
	 */
	FORCEINLINE void Disable() { IsEnabled = false; };

	/**
	 * Is component enabled
	 * Can be edit in Defaults only
	 * Can be read and write from Blueprint
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool IsEnabled;

		
};
