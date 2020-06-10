// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "AmmoWidget.generated.h"

class AGamesEducationCharacter;

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	/** Ammo Text Block */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AmmoText;
	
	/** Widget Constructor */
	virtual void NativeConstruct() override;

	/** On Character Update Ammo */
	void OnUpdateAmmo(int32 Ammo) const;
};
