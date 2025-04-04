// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team4_CH4_Project : ModuleRules
{
	public Team4_CH4_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });
	}
}
