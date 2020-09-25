using System;
using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.Platforms
{
    public class UWPPlatform : BasePlatform
    {
        public override PlatformType Type => PlatformType.UWP;

        public override string GetTargetFileName(ProjectKind kind, string name)
        {
            switch (kind)
            {
                case ProjectKind.ConsoleApp:
                case ProjectKind.GameApp:
                case ProjectKind.TestApp:
                case ProjectKind.DeveloperApp:
                    return $@"{name}.exe";
                case ProjectKind.SharedLib:
                    return $@"lib{name}.dll";
                case ProjectKind.StaticLib:
                    return $@"lib{name}.lib";
                case ProjectKind.HeaderLib:
                case ProjectKind.PrecompiledLib:
                    return name;
                default:
                    throw new Exception($@"Project kind {kind} is not supported");
            }
        }
    }
}
