// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "ActorVisualComponent.generated.h"

/**
 * Actor Visual Component - Visual representation of an Actor
 * Available for Blueprint implementation, Can Be spawned in Blueprint, belongs to ClassGroup "Visual"
 */
UCLASS(Blueprintable, ClassGroup=(Visual), meta=(BlueprintSpawnableComponent) )
class GAMESEDUCATION_API UActorVisualComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorVisualComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Offset for the Mesh Component
	 * Can be edin anywhere (Defaults and Instance)
	 * Can be read and write from a Blueprint
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Offset;

	/**
	 *	Update Mesh Offset
	 *	Can be implemented on C++ and in a Blueprint
	 *	Can be called from blueprint
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMeshOffset();
};
