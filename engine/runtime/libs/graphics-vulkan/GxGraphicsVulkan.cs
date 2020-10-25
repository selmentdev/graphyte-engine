using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsVulkan : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PrivateIncludePaths.Add("engine/runtime/libs/graphics-vulkan/public");

            target.AddPrivateDependency<GxGraphics>();
        }
    }
}
