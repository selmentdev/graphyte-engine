using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class GxLaunch : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.HeaderLib;
            result.PublicIncludes.Add("engine/runtime/libs/launch/public");
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxGeometry));
            result.Dependencies.Add(nameof(GxGraphics));
            result.Dependencies.Add(nameof(SdkFmt));

            if (configuration.Build == BuildType.Retail) {
                result.Dependencies.Add(nameof(GxGraphicsD3D11));
            }

            return result;
        }
    }
}
