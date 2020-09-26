using Graphyte.Build;

namespace Graphyte
{
    public class AppDemo : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.GameApplication;
            target.IncludePaths.Add("game/source/app.demo/public");

            target.Dependencies.AddRange(new[] {
                nameof(GxBase),
                nameof(GxGraphics),
                nameof(GxLaunch),
                nameof(GxRendering),
                nameof(GxGeometry),
            });
        }
    }
}
