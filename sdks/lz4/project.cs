using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class SdkLz4 : GraphyteBuildTool.Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.Kind = ProjectKind.StaticLib;
            result.PublicIncludes.Add("sdks/lz4/include");
            return result;
        }
    }
}
