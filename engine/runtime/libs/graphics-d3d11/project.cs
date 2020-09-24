using System;
using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class GxGraphicsD3D11 : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var platform = context.Selector.Platform;

            switch (platform)
            {
                case PlatformType.Windows:
                case PlatformType.UWP:
                    break;
                default:
                    return null;
            }

            var result = new ResolvedProject(this, context);

            if (context.Selector.Build == BuildType.Retail)
            {
                result.Kind = ProjectKind.StaticLib;
            }
            else
            {
                result.Kind = ProjectKind.SharedLib;
            }

            result.PublicIncludes.Add("engine/runtime/libs/graphics-d3d11/public");
            result.Dependencies.Add(nameof(SdkFmt));
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxGraphics));
            result.Libraries.AddRange(new [] {
                "dxgi.lib",
                "d3d11.lib",
                "dxguid.lib",
                "User32.lib",
            });

            return result;
        }
    }
}
