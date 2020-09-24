using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte{
    public class SdkSqlite : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.Kind = ProjectKind.StaticLib;
            result.PublicIncludes.Add("sdks/sqlite/include");
            return result;
        }
    }
}
