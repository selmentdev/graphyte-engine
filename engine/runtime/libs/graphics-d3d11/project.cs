using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class GxGraphicsD3D11 : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            switch (configuration.Platform)
            {
                case PlatformType.Windows:
                case PlatformType.UWP:
                    break;
                default:
                    return null;
            }

            var result = new ProjectDefinition(this);

            if (configuration.Build == BuildType.Retail)
            {
                result.Kind = ProjectKind.StaticLib;
            }
            else
            {
                result.Kind = ProjectKind.SharedLib;
            }

            result.PublicIncludes.Add("engine/runtime/libs/graphics-d3d11/public");
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxGraphics));
            result.Dependencies.Add(nameof(SdkFmt));
            result.Libraries.AddRange(new[] {
                "dxgi.lib",
                "d3d11.lib",
                "dxguid.lib",
                "User32.lib",
            });

            return result;
        }
    }
}
