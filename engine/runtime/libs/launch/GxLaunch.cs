using Graphyte.Build;
using Graphyte.Build.Platforms;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class GxLaunch : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.HeaderLibrary;
            target.PublicIncludePaths.Add("engine/runtime/libs/launch/public");

            target.AddPublicDependency<GxBase>();
            target.AddPublicDependency<GxGeometry>();
            target.AddPublicDependency<GxGraphics>();

            target.AddPublicDependency<GxGraphicsD3D11>();

            if (target.PlatformType == PlatformType.UniversalWindows)
            {
                target.PublicLibraries.Add("WindowsApp.lib");
            }
            else if (target.PlatformType == PlatformType.Windows)
            {
                target.PublicLibraries.AddRange(new[]
                {
                    "Mincore.lib",
                    "user32.lib",
                    "shell32.lib",
                });
            }
        }
    }
}
