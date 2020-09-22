// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatMessageWidget.h"

void UChatMessageWidget::SetMessageText(const FText NewText) const
{
    if (MessageText)
    {
        MessageText->SetText(NewText);
    }
}
