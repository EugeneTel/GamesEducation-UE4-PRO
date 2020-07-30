// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEDUCATION_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* ScoreText;
    
    /** Widget Constructor */
    virtual void NativeConstruct() override;

    /** On Update Player Score */
    void OnUpdateScore(int32 Score) const;
};
