using Graphyte.Build;

namespace Graphyte
{
    public class GxGeometry : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PublicIncludePaths.Add("engine/runtime/libs/geometry/public");

            target.AddPublicDependency<GxBase>();
        }
    }
}
