// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class EDITORBUTTONBUILDER_API FActorBuilderDetails : public IDetailCustomization
{
public:
	FActorBuilderDetails();
	~FActorBuilderDetails();

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	FReply OnBuildClicked();
};
