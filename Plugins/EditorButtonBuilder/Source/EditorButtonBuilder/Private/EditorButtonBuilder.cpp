// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EditorButtonBuilder.h"
#include "Builder.h"
#include "FActorBuilderDetails.h"
#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "FEditorButtonBuilderModule"

void FEditorButtonBuilderModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// Add custom builder details for all instances of ABuilder 
	PropertyModule.RegisterCustomClassLayout(ABuilder::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FActorBuilderDetails::MakeInstance));
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FEditorButtonBuilderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorButtonBuilderModule, EditorButtonBuilder)