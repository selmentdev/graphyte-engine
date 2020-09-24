using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte{
    public class SdkCatch2 : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.Kind = ProjectKind.HeaderLib;
            result.PublicIncludes.Add("sdks/catch2/include");
            return result;
        }
    }
}
