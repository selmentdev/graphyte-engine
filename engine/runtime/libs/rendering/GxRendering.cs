using Graphyte.Build;

namespace Graphyte
{
    public class GxRendering : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/rendering/public");

            target.AddPublicDependency<GxGraphics>();
        }
    }
}
