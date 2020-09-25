using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.Platforms
{
    public abstract class BasePlatform
    {
        public abstract PlatformType Type { get; }
        public abstract string GetTargetFileName(ProjectKind kind, string name);
    }
}
