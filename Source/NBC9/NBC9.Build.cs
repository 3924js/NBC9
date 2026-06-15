// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NBC9 : ModuleRules
{
	public NBC9(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			//기본 모듈
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			
			//UI 관련 모듈
			"UMG", "Slate", "SlateCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] { "Game"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
