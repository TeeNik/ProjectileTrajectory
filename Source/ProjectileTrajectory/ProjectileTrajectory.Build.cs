// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectileTrajectory : ModuleRules
{
	public ProjectileTrajectory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
