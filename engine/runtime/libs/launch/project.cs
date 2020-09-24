using System;
using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class GxLaunch : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.Kind = ProjectKind.HeaderLib;
            result.PublicIncludes.Add("engine/runtime/libs/launch/public");
            return result;
        }
    }
}
