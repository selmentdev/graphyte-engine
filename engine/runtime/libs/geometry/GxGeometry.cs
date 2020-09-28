using Graphyte.Build;

namespace Graphyte
{
    public class GxGeometry : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/geometry/public");

            target.AddPublicDependency<GxBase>();
        }
    }
}
