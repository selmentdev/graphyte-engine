using System;
using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.Platforms
{
    public class LinuxPlatform : BasePlatform
    {
        public override PlatformType Type => PlatformType.Windows;

        public override string GetTargetFileName(ProjectKind kind, string name)
        {
            switch (kind)
            {
                case ProjectKind.ConsoleApp:
                case ProjectKind.GameApp:
                case ProjectKind.TestApp:
                case ProjectKind.DeveloperApp:
                    return $@"{name}.elf";
                case ProjectKind.SharedLib:
                    return $@"lib{name}.so";
                case ProjectKind.StaticLib:
                    return $@"lib{name}.a";
                case ProjectKind.HeaderLib:
                case ProjectKind.PrecompiledLib:
                    return name;
                default:
                    throw new Exception($@"Project kind {kind} is not supported");
            }
        }
    }
}
