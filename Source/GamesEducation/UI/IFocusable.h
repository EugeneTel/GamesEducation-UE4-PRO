// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IFocusable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIFocusable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMESEDUCATION_API IIFocusable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetIndex() = 0;

	virtual void SetIndex(int32 Index) = 0;

	virtual bool IsInFocus() = 0;

	virtual void Focus() = 0;

	virtual void UnFocus() = 0;

	virtual void OnButtonReleased() = 0;
};
