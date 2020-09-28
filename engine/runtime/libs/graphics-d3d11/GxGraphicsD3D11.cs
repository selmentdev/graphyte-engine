using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsD3D11 : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/graphics-d3d11/public");

            target.AddPrivateDependency<GxGraphics>();

            target.Libraries.AddRange(new[]
            {
                "dxgi.lib",
                "d3d11.lib",
                "dxguid.lib",
                "User32.lib",
            });
        }
    }
}
