using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class AppDemo : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.Application;
            target.PublicIncludePaths.Add("game/source/app.demo/public");

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxGraphics>();
            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxRendering>();
            target.AddPrivateDependency<GxGeometry>();
        }
    }
}
