using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class GxTestExecutor : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.HeaderLib;
            result.Dependencies.Add(nameof(GxLaunch));
            return result;
        }
    }
}
