using Graphyte.Build;

namespace Graphyte
{
    public class MainSolution : Solution
    {
        public static class Builds
        {
            public static readonly BuildType Developer = new BuildType("Developer");
            public static readonly BuildType Testing = new BuildType("Testing");
            public static readonly BuildType Retail = new BuildType("Retail");
        }

        public static class Configurations
        {
            public static readonly ConfigurationType Release = new ConfigurationType("Release");
            public static readonly ConfigurationType Profile = new ConfigurationType("Profile");
            public static readonly ConfigurationType Checked = new ConfigurationType("Checked");
            public static readonly ConfigurationType Debug = new ConfigurationType("Debug");
        }

        public MainSolution()
        {
            this.Name = "Graphyte";

            this.AddTarget(new TargetType(PlatformType.Windows, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.Windows, ArchitectureType.ARMv8));

            this.AddTarget(new TargetType(PlatformType.UWP, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.UWP, ArchitectureType.ARMv8));

            this.AddTarget(new TargetType(PlatformType.Linux, ArchitectureType.X64));
            this.AddTarget(new TargetType(PlatformType.Linux, ArchitectureType.ARMv8));

            this.AddBuildType(Builds.Developer);
            this.AddBuildType(Builds.Testing);
            this.AddBuildType(Builds.Retail);

            this.AddConfigurationType(Configurations.Debug);
            this.AddConfigurationType(Configurations.Checked);
            this.AddConfigurationType(Configurations.Release);
            this.AddConfigurationType(Configurations.Profile);

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
            if (configuration.Build == MainSolution.Builds.Retail)
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
