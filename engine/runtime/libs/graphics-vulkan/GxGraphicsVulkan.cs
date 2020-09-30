using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsVulkan : ModuleProject
    {
        public override void Configure(Target target, IContext configuration)
        {
            base.Configure(target, configuration);

            target.PrivateIncludePaths.Add("engine/runtime/libs/graphics-vulkan/public");

            target.AddPrivateDependency<GxGraphics>();
        }
    }
}
