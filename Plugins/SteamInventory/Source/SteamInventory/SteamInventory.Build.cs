// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SteamInventory : ModuleRules
{
	public SteamInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Steamworks",
				// ... add private dependencies that you statically link with here ...	
			}
			);

		PublicDelayLoadDLLs.Add("steam_api64.dll");

		string SteamVersion = "Steamv157";
		string SDKPath = Path.Combine(EngineDirectory, "Source/ThirdParty/Steamworks", SteamVersion, "sdk/redistributable_bin/win64/steam_api64.dll");

		RuntimeDependencies.Add(SDKPath);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
