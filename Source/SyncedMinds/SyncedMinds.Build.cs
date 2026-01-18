// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SyncedMinds : ModuleRules
{
	public SyncedMinds(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite", "AITestSuite" });

		PublicIncludePaths.AddRange(new string[] {
			"SyncedMinds",
			"SyncedMinds/Variant_Platforming",
			"SyncedMinds/Variant_Platforming/Animation",
			"SyncedMinds/Variant_Combat",
			"SyncedMinds/Variant_Combat/AI",
			"SyncedMinds/Variant_Combat/Animation",
			"SyncedMinds/Variant_Combat/Gameplay",
			"SyncedMinds/Variant_Combat/Interfaces",
			"SyncedMinds/Variant_Combat/UI",
			"SyncedMinds/Variant_SideScrolling",
			"SyncedMinds/Variant_SideScrolling/AI",
			"SyncedMinds/Variant_SideScrolling/Gameplay",
			"SyncedMinds/Variant_SideScrolling/Interfaces",
			"SyncedMinds/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
