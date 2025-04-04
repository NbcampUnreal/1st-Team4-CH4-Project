using UnrealBuildTool;

public class Team4_CH4_Project : ModuleRules
{
    public Team4_CH4_Project(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "AnimGraphRuntime"   
        });

        PublicIncludePaths.AddRange(new string[] {
            "Team4_CH4_Project/Character",
            "Team4_CH4_Project/Animation"
        });

    }
}
