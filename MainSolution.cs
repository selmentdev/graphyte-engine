using Graphyte.Build;

namespace Generate
{
    class Program
    {
        static int Main(string[] args)
        {
            return Graphyte.Build.Application.Main(args);
        }
    }
}

namespace Graphyte
{
    public sealed class EngineFeatures : BaseProfileSection
    {
        public bool? MemoryTracing { get; set; }
        public bool? Profiling { get; set; }
    }

    public sealed class ProductInfo : BaseProfileSection
    {
        public string Name { get; set; }
        public string Company { get; set; }
        public string Version { get; set; }
    }

    public class MainSolution : Solution
    {
        public MainSolution()
        {
            this.Name = "Graphyte";

            // Modules
            this.AddProject(new GxBase());
#if true
            this.AddProject(new GxGeometry());
            this.AddProject(new GxGraphics());
            this.AddProject(new GxGraphicsD3D11());
            this.AddProject(new GxGraphicsD3D12());
            this.AddProject(new GxGraphicsGLCore());
            this.AddProject(new GxGraphicsVulkan());
            this.AddProject(new GxLaunch());
            this.AddProject(new GxRendering());
#endif
            // Sdks
            this.AddProject(new SdkCatch2());
            this.AddProject(new SdkFmt());
            this.AddProject(new SdkLz4());
            this.AddProject(new SdkMbedtls());
            this.AddProject(new SdkSqlite());
            this.AddProject(new SdkVulkanVma());

#if true
            // Tests
            this.AddProject(new GxTestExecutor());
            this.AddProject(new TestGxBase());
            this.AddProject(new TestGxEntities());
            this.AddProject(new TestGxGraphics());
            this.AddProject(new TestGxMaths());

            // Developer tools
            this.AddProject(new DevAssetsCompiler());
            this.AddProject(new DevLogFix());
            this.AddProject(new GxAssetsBase());
            this.AddProject(new GxAssetsMesh());
            this.AddProject(new GxAssetsShader());

            // Applications
            this.AddProject(new AppDemo());
#endif
        }

        public override void PreConfigure(Target target)
        {
            base.PreConfigure(target);
        }

        public override void PostConfigure(Target target)
        {
            base.PostConfigure(target);

            if (target.PlatformType == PlatformType.UniversalWindows && target.TargetType.IsApplication())
            {
                // TODO: This should be added by platform matcher
                target.PublicLibraries.Add("WindowsApp.lib");
            }
        }
    }

    public class ModuleProject : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = target.ConfigurationType == ConfigurationType.Release
                ? TargetType.StaticLibrary
                : TargetType.SharedLibrary;
        }
    }
}
