using Graphyte.Build;

namespace Graphyte
{
    public class GxLaunch : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.HeaderLib;
            target.IncludePaths.Add("engine/runtime/libs/launch/public");
            target.Dependencies.Add(nameof(GxBase));
            target.Dependencies.Add(nameof(GxGeometry));
            target.Dependencies.Add(nameof(GxGraphics));
            target.Dependencies.Add(nameof(SdkFmt));

            if (configuration.Build == MainSolution.Builds.Retail)
            {
                target.Dependencies.Add(nameof(GxGraphicsD3D11));
            }

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
