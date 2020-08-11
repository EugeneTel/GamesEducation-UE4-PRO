// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitComboWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UHitComboWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	/** Number of hits */
	int32 HitCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTCombo;

	void UpdateComboCount(int32 Value);

	void ResetCombo() const;

	void StoreWidgetAnimations();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

protected:

	/** Called On Enemy Hit Event */
	void OnEnemyHit(AActor* HitActor);

	/** Called on Shoot Missing Event */
	void OnShootMiss();
	
	UPROPERTY()
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* ComboFadeAnimation;
	
	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* ComboShakeAnimation;
};
