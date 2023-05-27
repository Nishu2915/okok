// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GDTVGameJam : ModuleRules
{
	public GDTVGameJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "LoadingScreen",
                "MotionWarping"
            }
        );

        //PublicIncludePaths.AddRange(new string[] { "LoadingScreen/Public", "LoadingScreen/Private" }); //include inside module instead

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
                System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Plugins/Animation/MotionWarping/Source/MotionWarping/Public",
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
				//Engine folder might be different from each version or building from source.
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Plugins/Animation/MotionWarping/Source/MotionWarping/Private",
            }
            );


        PublicIncludePaths.Add("GDTVGameJam/");
        
    }
}
