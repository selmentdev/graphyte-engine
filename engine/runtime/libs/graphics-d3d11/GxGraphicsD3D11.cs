using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsD3D11 : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PrivateIncludePaths.Add("engine/runtime/libs/graphics-d3d11/public");

            target.AddPrivateDependency<GxGraphics>();

            target.PrivateLibraries.AddRange(new[]
            {
                "dxgi.lib",
                "d3d11.lib",
                "dxguid.lib",
                "User32.lib",
            });
        }
    }
}
