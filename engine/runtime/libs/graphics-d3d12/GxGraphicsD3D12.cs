using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class GxGraphicsD3D12 : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PrivateIncludePaths.Add("engine/runtime/libs/graphics-d3d12/public");

            target.AddPrivateDependency<GxGraphics>();

            target.PrivateLibraries.AddRange(new[]
            {
                "dxgi.lib",
                "d3d12.lib",
                "dxguid.lib",
                "User32.lib",
            });
        }
    }
}
