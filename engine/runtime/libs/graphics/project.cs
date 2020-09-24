using System;
using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class GxGraphics : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);

            if (context.Selector.Build == BuildType.Retail)
            {
                result.Kind = ProjectKind.StaticLib;
            }
            else
            {
                result.Kind = ProjectKind.SharedLib;
            }

            result.PublicIncludes.Add("engine/runtime/libs/graphics/public");
            result.Dependencies.Add(nameof(SdkFmt));
            result.Dependencies.Add(nameof(GxBase));
            return result;
        }
    }
}
