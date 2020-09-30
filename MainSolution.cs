using Graphyte.Build;

namespace Graphyte
{
    public class MainSolution : Solution
    {
        public MainSolution()
        {
            this.Name = "Graphyte";

            this.AddTargetTuple(PlatformType.Windows, ArchitectureType.X64);
            this.AddTargetTuple(PlatformType.Windows, ArchitectureType.Arm64);

            this.AddTargetTuple(PlatformType.UWP, ArchitectureType.X64);
            this.AddTargetTuple(PlatformType.UWP, ArchitectureType.Arm64);

            this.AddTargetTuple(PlatformType.Linux, ArchitectureType.X64);
            this.AddTargetTuple(PlatformType.Linux, ArchitectureType.Arm64);

            this.AddBuildType(BuildType.Developer);
            this.AddBuildType(BuildType.Testing);
            this.AddBuildType(BuildType.Retail);

            this.AddConfigurationType(ConfigurationType.Debug);
            this.AddConfigurationType(ConfigurationType.Checked);
            this.AddConfigurationType(ConfigurationType.Release);
            this.AddConfigurationType(ConfigurationType.Profile);

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

        protected override void PreConfigureTarget(Target target, IContext context)
        {
            base.PreConfigureTarget(target, context);
        }

        protected override void PostConfigureTarget(Target target, IContext context)
        {
            base.PostConfigureTarget(target, context);

            if (context.Platform == PlatformType.UWP && target.Type.IsApplication())
            {
                // TODO: This should be added by platform matcher
                target.PublicLibraries.Add("WindowsApp.lib");
            }
        }
    }

    public class ModuleProject : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            if (configuration.Build == BuildType.Retail)
            {
                target.Type = TargetType.StaticLibrary;
            }
            else
            {
                target.Type = TargetType.SharedLibrary;
            }
        }
    }
}
