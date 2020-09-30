using Graphyte.Build;

namespace Graphyte
{
    public class AppDemo : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.Application;
            target.PublicIncludePaths.Add("game/source/app.demo/public");

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxGraphics>();
            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxRendering>();
            target.AddPrivateDependency<GxGeometry>();
        }
    }
}
