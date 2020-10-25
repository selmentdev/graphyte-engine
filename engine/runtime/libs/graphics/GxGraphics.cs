using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphics : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PublicIncludePaths.Add("engine/runtime/libs/graphics/public");

            target.AddPublicDependency<GxBase>();
        }
    }
}
