using Graphyte.Build;

namespace Graphyte
{
    public class GxRendering : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PublicIncludePaths.Add("engine/runtime/libs/rendering/public");

            target.AddPublicDependency<GxGraphics>();
        }
    }
}
