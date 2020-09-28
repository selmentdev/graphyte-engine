using Graphyte.Build;

namespace Graphyte
{
    public class AppDemo : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.GameApplication;
            target.IncludePaths.Add("game/source/app.demo/public");

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxGraphics>();
            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxRendering>();
            target.AddPrivateDependency<GxGeometry>();
        }
    }
}
