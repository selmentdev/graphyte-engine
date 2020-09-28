using Graphyte.Build;

namespace Graphyte
{
    public class GxLaunch : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.HeaderLib;
            target.IncludePaths.Add("engine/runtime/libs/launch/public");

            target.AddPublicDependency<GxBase>();
            target.AddPublicDependency<GxGeometry>();
            target.AddPublicDependency<GxGraphics>();

            target.AddPublicDependency<GxGraphicsD3D11>();

            if (configuration.Platform == PlatformType.UWP)
            {
                target.Libraries.Add("WindowsApp.lib");
            }
            else if (configuration.Platform == PlatformType.Windows)
            {
                target.Libraries.AddRange(new[]
                {
                    "Mincore.lib",
                    "user32.lib",
                    "shell32.lib",
                });
            }
        }
    }
}
