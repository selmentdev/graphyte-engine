using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class AppDemo : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.PublicIncludes.Add("game/source/app.demo/public");
            result.Kind = ProjectKind.GameApp;
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxGraphics));
            result.Dependencies.Add(nameof(GxLaunch));
            result.Dependencies.Add(nameof(GxRendering));
            result.Dependencies.Add(nameof(GxGeometry));

            if (configuration.Platform == PlatformType.UWP)
            {
                result.Libraries.Add("WindowsApp.lib");
            }
            return result;
        }
    }
}
