using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class TestGxBase : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.TestApp;
            result.Dependencies.Add(nameof(GxBase));
            result.Dependencies.Add(nameof(GxTestExecutor));
            return result;
        }
    }
}
