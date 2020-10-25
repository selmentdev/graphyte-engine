using Graphyte.Build;
using System;

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
    public class MainSolution : Solution
    {
        public MainSolution()
        {
            this.Name = "Graphyte";

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

        public override void PreConfigure(Target target)
        {
            base.PreConfigure(target);
        }

        public override void PostConfigure(Target target)
        {
            base.PostConfigure(target);

            if (target.TargetTuple.Platform == Platform.UWP && target.TargetType.IsApplication())
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
            if (target.TargetTuple.Configuration == Configuration.Release)
            {
                target.TargetType = TargetType.StaticLibrary;
            }
            else
            {
                target.TargetType = TargetType.SharedLibrary;
            }
        }
    }
}
