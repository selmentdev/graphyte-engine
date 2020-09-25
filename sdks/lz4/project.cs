using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class SdkLz4 : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.StaticLib;
            result.PublicIncludes.Add("sdks/lz4/include");
            return result;
        }
    }
}
