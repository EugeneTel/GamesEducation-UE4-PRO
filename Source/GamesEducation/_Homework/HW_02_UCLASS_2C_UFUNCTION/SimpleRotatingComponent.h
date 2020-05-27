// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorBehaviorComponent.h"
#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "Components/ActorComponent.h"
#include "SimpleRotatingComponent.generated.h"

/**
 * Simple Rotation Component - Rotating the Owning Actor
 * Available for Blueprint implementation, Can Be spawned in Blueprint, belongs to ClassGroup "Behavior"
 */
UCLASS(Blueprintable, ClassGroup=(Behavior), meta=(BlueprintSpawnableComponent, ToolTip="Simple Rotation Component") )
class GAMESEDUCATION_API USimpleRotatingComponent : public UActorBehaviorComponent, public IInteractableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleRotatingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	/**
	 * Rotate the Actor
	 * Can be called from Blueprint
	 */
	UFUNCTION(BlueprintCallable)
	void RotateTick(float DeltaTime) const;

	/**
	 * Rotation speed per second
	 * Can be edit in Defaults (blueprint) and in an Instance (if added to a scene)
	 * Can be read read only from Blueprint
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed;
};
