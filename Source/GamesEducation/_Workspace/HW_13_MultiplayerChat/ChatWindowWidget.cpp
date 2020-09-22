// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWindowWidget.h"

#include "ChatMessageWidget.h"
#include "GamesEducation/GamesEducationHUD.h"
#include "GamesEducation/GEPlayerController.h"

void UChatWindowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (SendButton)
    {
        SendButton->OnClicked.AddDynamic(this, &UChatWindowWidget::OnSendButtonClicked);
    }

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UChatWindowWidget::OnCloseButtonClicked);
    }
}

void UChatWindowWidget::AddMessage(const FText Message) const
{
    const TSubclassOf<UChatMessageWidget> WidgetClass = MessageWidgetClass ? MessageWidgetClass : UChatMessageWidget::StaticClass();
    UChatMessageWidget* NewMessageWidget = CreateWidget<UChatMessageWidget>(GetWorld(), WidgetClass);
    NewMessageWidget->SetMessageText(Message);
    if (ChatScrollBox)
    {
        ChatScrollBox->AddChild(NewMessageWidget);
    }
}

void UChatWindowWidget::OnSendButtonClicked()
{
    if (!NewMessageTextBox)
        return;

    const FText Message = NewMessageTextBox->GetText();
    if (!Message.IsEmpty())
    {
        AGEPlayerController* PlayerController = Cast<AGEPlayerController>(GetOwningPlayer());
        PlayerController->SendChatMessage(Message);
    }
    NewMessageTextBox->SetText(FText::GetEmpty());
}

void UChatWindowWidget::OnCloseButtonClicked()
{
    AGEPlayerController* PlayerController = Cast<AGEPlayerController>(GetOwningPlayer());
    AGamesEducationHUD* CurrentHUD = Cast<AGamesEducationHUD>(PlayerController->GetHUD());
    CurrentHUD->HideChatWidget();
}
