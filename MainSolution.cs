using Graphyte.Build;

namespace Graphyte
{
    public class MainSolution : Solution
    {
        public MainSolution()
        {
            this.Name = "Graphyte";

            this.AddTarget(new TargetType(PlatformType.Windows, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.Windows, ArchitectureType.ARMv8));

            this.AddTarget(new TargetType(PlatformType.UWP, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.UWP, ArchitectureType.ARMv8));

            this.AddTarget(new TargetType(PlatformType.Linux, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.Linux, ArchitectureType.ARMv8));

            this.AddBuildType(BuildType.Developer);
            this.AddBuildType(BuildType.Testing);
            this.AddBuildType(BuildType.Retail);

            this.AddConfigurationType(ConfigurationType.Debug);
            this.AddConfigurationType(ConfigurationType.Checked);
            this.AddConfigurationType(ConfigurationType.Release);
            this.AddConfigurationType(ConfigurationType.Profile);

            // Applications
            this.AddProject<AppDemo>();

            // Modules
            this.AddProject<GxBase>();
            this.AddProject<GxGeometry>();
            this.AddProject<GxGraphics>();
            this.AddProject<GxGraphicsD3D11>();
            this.AddProject<GxGraphicsD3D12>();
            this.AddProject<GxGraphicsGLCore>();
            this.AddProject<GxGraphicsVulkan>();
            this.AddProject<GxLaunch>();
            this.AddProject<GxRendering>();

            // Sdks
            this.AddProject<SdkCatch2>();
            this.AddProject<SdkFmt>();
            this.AddProject<SdkLz4>();
            this.AddProject<SdkMbedtls>();
            this.AddProject<SdkSqlite>();
            this.AddProject<SdkVulkanVma>();

            // Tests
            this.AddProject<GxTestExecutor>();
            this.AddProject<TestGxBase>();
            this.AddProject<TestGxEntities>();
            this.AddProject<TestGxGraphics>();
            this.AddProject<TestGxMaths>();

            // Developer tools
            this.AddProject<DevAssetsCompiler>();
            this.AddProject<DevLogFix>();
            this.AddProject<GxAssetsBase>();
            this.AddProject<GxAssetsMesh>();
            this.AddProject<GxAssetsShader>();
        }

        public override void PreConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
            base.PreConfigure(target, context);

            target.PrivateIncludePaths.Add("engine/include");
        }

        public override void PostConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
            base.PostConfigure(target, context);

            if (context.Platform == PlatformType.UWP && target.Type.IsApplication())
            {
                // TODO: This should be added by platform matcher
                target.Libraries.Add("WindowsApp.lib");
            }
        }
    }

    public class ModuleProject : Project
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
