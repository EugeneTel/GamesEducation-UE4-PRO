// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionSystemActor.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
AReflectionSystemActor::AReflectionSystemActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AReflectionSystemActor::BeginPlay()
{
	Super::BeginPlay();

	// BP function name for printing the variable name
	const TCHAR* FunctionName = TEXT("TestFunction");

	// Print an Initial value of the BP variable
	CallBlueprintFunction(FunctionName);

	// Read and update the BP variable
	IncreaseBlueprintVariable(TEXT("TestFloat"));

	// Print the Final value of the BP variable
	CallBlueprintFunction(FunctionName);
}


void AReflectionSystemActor::IncreaseBlueprintVariable(const FName VariableName)
{
	// Get a BP Variable
	UFloatProperty* FloatProp = FindField<UFloatProperty>(this->GetClass(), VariableName);

	if (FloatProp == nullptr)
		return;

	float FloatValue = FloatProp->GetPropertyValue_InContainer(this);

	UE_LOG(LogTemp, Warning, TEXT("Current value in BP: %f"), FloatValue);

	// Increase and Set the BP Variable
	FloatValue++;
	FloatProp->SetPropertyValue_InContainer(this, FloatValue);
}


void AReflectionSystemActor::CallBlueprintFunction(const FName FunctionName)
{
	// Call a function defined only in Blueprint for printing the BP variable result
	FOutputDeviceNull Ar;
	this->CallFunctionByNameWithArguments(*FunctionName.ToString(), Ar, this, true);
}

