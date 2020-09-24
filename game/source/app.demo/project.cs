using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class AppDemo : GraphyteBuildTool.Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.PublicIncludes.Add("game/source/app.demo/public");
            result.Kind = ProjectKind.GameApp;
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxGraphics));
            result.Dependencies.Add(nameof(GxLaunch));
            result.Dependencies.Add(nameof(GxRendering));
            result.Dependencies.Add(nameof(GxGeometry));

            if (context.Selector.Platform == PlatformType.UWP) {
                result.Libraries.Add("WindowsApp.lib");
            }
            return result;
        }
    }
}
