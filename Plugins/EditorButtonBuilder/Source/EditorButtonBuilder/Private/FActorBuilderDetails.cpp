// Fill out your copyright notice in the Description page of Project Settings.


#include "FActorBuilderDetails.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Text/STextBlock.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "FActorBuilderDetails"

FActorBuilderDetails::FActorBuilderDetails()
{
}

FActorBuilderDetails::~FActorBuilderDetails()
{
}

TSharedRef<IDetailCustomization> FActorBuilderDetails::MakeInstance()
{
    return MakeShareable(new FActorBuilderDetails);
}

void FActorBuilderDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    // Create category in details similar to uproperty category tag for blueprints
    IDetailCategoryBuilder& EngineCategory = DetailBuilder.EditCategory("OwnEngine" );

    const FText SampleButton = LOCTEXT("BuildBtn", "BuildBtn");

    // Using Slate create a button
    EngineCategory.AddCustomRow(SampleButton, false)
    .NameContent()
    [
        SNullWidget::NullWidget
    ]
    .ValueContent()
    .VAlign(VAlign_Center)
    .MaxDesiredWidth(300)
    [
        SNew(SButton)
        .ToolTipText(LOCTEXT("Cool stuff", "Really Cool"))
        .OnClicked(this, &FActorBuilderDetails::OnBuildClicked)
        .Content()
        [
            SNew(STextBlock)
            .Text(SampleButton)
        ]
    ];
}

FReply FActorBuilderDetails::OnBuildClicked()
{
    return FReply::Handled();
}
