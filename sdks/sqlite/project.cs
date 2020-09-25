using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class SdkSqlite : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.StaticLib;
            result.PublicIncludes.Add("sdks/sqlite/include");
            return result;
        }
    }
}
