// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamesEducation : ModuleRules
{
	public GamesEducation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ProceduralMeshComponent",
			"DesktopPlatform", "Debug", "Slate", "SlateCore", "AnimationCore", "AnimGraphRuntime", "AIModule",
			"ApexDestruction"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
