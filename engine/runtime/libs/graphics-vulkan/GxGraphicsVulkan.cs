using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsVulkan : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/graphics-vulkan/public");

            target.AddPrivateDependency<GxGraphics>();
        }
    }
}
