using Graphyte.Build;

namespace Graphyte
{
    public class GxGraphicsGLCore : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/graphics-opengl/public");
            target.Dependencies.AddRange(new[]
            {
                nameof(GxBase),
                nameof(GxGraphics),
            });
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
