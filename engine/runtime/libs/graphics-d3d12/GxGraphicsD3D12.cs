using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsD3D12 : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/graphics-d3d12/public");
            target.Dependencies.AddRange(new[]
            {
                nameof(GxBase),
                nameof(GxGraphics),
            });
            target.Libraries.AddRange(new[]
            {
                "dxgi.lib",
                "d3d12.lib",
                "dxguid.lib",
                "User32.lib",
            });
        }
    }
}
