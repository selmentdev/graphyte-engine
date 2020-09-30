using Graphyte.Build;

namespace Graphyte
{
    public class GxGeometry : ModuleProject
    {
        public override void Configure(Target target, IContext configuration)
        {
            base.Configure(target, configuration);

            target.PublicIncludePaths.Add("engine/runtime/libs/geometry/public");

            target.AddPublicDependency<GxBase>();
        }
    }
}
