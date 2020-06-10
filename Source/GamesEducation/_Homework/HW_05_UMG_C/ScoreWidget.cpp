// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "GamesEducation/GamesEducationCharacter.h"
#include "Components/TextBlock.h"

void UScoreWidget::NativeConstruct()
{
    AGamesEducationCharacter::NotifyUpdateScore.AddUObject(this, &UScoreWidget::OnUpdateScore);
}

void UScoreWidget::OnUpdateScore(const int32 Score) const
{
    ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}
