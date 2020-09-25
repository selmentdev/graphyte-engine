using System.Collections.Generic;
using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class SdkCatch2 : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.HeaderLib;
            result.PublicIncludes.Add("sdks/catch2/include");
            return result;
        }
    }
}
