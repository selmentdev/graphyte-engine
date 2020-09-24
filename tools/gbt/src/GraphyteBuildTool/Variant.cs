using System.Collections.Generic;

namespace GraphyteBuildTool
{
    public enum PlatformType
    {
        Windows,
        Linux,
        UWP,
        MacOS,
        Android,
        IOS,
        NX,
        Orbis,
        Prospero,
        Durango,
        GDK,
    }

    public enum ArchitectureType
    {
        X64,
        ARM64,
        PPC64,
    }

    public enum BuildType
    {
        Developer,
        Testing,
        Retail,
    }

    public enum ConfigType
    {
        Debug,
        Checked,
        Profile,
        Release,
    }

    public enum ProjectKind
    {
        ConsoleApp,
        GameApp,
        TestApp,
        DeveloperApp,
        SharedLib,
        StaticLib,
        HeaderLib,
        PrecompiledLib,
    }
}

namespace GraphyteBuildTool
{
    public struct VariantSelector
    {
        public PlatformType Platform { get; set; }
        public ArchitectureType Architecture { get; set; }
        public BuildType Build { get; set; }
        public ConfigType Config { get; set; }
        public PlatformType PlatformType { get; internal set; }

        public override string ToString()
        {
            return $@"(`{this.Platform}`, `{this.Architecture}`, `{this.Build}`, `{this.Config}`)";
        }
    }
}
