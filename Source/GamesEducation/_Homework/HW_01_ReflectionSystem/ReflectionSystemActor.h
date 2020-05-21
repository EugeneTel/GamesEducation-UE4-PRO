// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReflectionSystemActor.generated.h"

UCLASS()
class GAMESEDUCATION_API AReflectionSystemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReflectionSystemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Read a Blueprint defined only variable and change it
	UFUNCTION(BlueprintCallable)
	void IncreaseBlueprintVariable(FName VariableName);

	// Call a Blueprint defined only function for display the BP Variable value
	UFUNCTION(BlueprintCallable)
	void CallBlueprintFunction(const FName FunctionName);

};
