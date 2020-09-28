using Graphyte.Build;

namespace Graphyte
{
    public class MainSolution : Solution
    {
        public MainSolution()
        {
            this.Name = "Graphyte";

            this.AddTarget(PlatformType.Windows, ArchitectureType.X64);
            this.AddTarget(PlatformType.Windows, ArchitectureType.Arm64);

            this.AddTarget(PlatformType.UWP, ArchitectureType.X64);
            this.AddTarget(PlatformType.UWP, ArchitectureType.Arm64);

            this.AddTarget(PlatformType.Linux, ArchitectureType.X64);
            this.AddTarget(PlatformType.Linux, ArchitectureType.Arm64);

            this.AddBuild(BuildType.Developer);
            this.AddBuild(BuildType.Testing);
            this.AddBuild(BuildType.Retail);

            this.AddConfiguration(ConfigurationType.Debug);
            this.AddConfiguration(ConfigurationType.Checked);
            this.AddConfiguration(ConfigurationType.Release);
            this.AddConfiguration(ConfigurationType.Profile);

            // Applications
            this.AddProject(new AppDemo());

            // Modules
            this.AddProject(new GxBase());
            this.AddProject(new GxGeometry());
            this.AddProject(new GxGraphics());
            this.AddProject(new GxGraphicsD3D11());
            this.AddProject(new GxGraphicsD3D12());
            this.AddProject(new GxGraphicsGLCore());
            this.AddProject(new GxGraphicsVulkan());
            this.AddProject(new GxLaunch());
            this.AddProject(new GxRendering());

            // Sdks
            this.AddProject(new SdkCatch2());
            this.AddProject(new SdkFmt());
            this.AddProject(new SdkLz4());
            this.AddProject(new SdkMbedtls());
            this.AddProject(new SdkSqlite());
            this.AddProject(new SdkVulkanVma());

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
        }

        protected override void PreConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
            base.PreConfigure(target, context);
        }

        protected override void PostConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
            base.PostConfigure(target, context);

            if (context.Platform == PlatformType.UWP && target.Type.IsApplication())
            {
                // TODO: This should be added by platform matcher
                target.Libraries.Add("WindowsApp.lib");
            }
        }
    }

    public class ModuleProject : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            if (configuration.Build == BuildType.Retail)
            {
                target.Type = OutputType.StaticLib;
            }
            else
            {
                target.Type = OutputType.SharedLib;
            }
        }
    }
}
