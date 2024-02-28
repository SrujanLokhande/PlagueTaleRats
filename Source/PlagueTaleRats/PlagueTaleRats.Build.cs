// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlagueTaleRats : ModuleRules
{
	public PlagueTaleRats(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Niagara", "Slate", "SlateCore" });
	}
}
