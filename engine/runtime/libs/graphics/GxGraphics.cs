using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphics : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);
            target.IncludePaths.Add("engine/runtime/libs/graphics/public");

            target.AddPublicDependency<GxBase>();
        }
    }
}
