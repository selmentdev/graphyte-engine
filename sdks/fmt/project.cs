using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte
{
    public class SdkFmt : GraphyteBuildTool.Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.PublicIncludes.Add("sdks/fmt/include");
            result.PublicDefines["FMT_EXCEPTIONS"] = "1";
            result.PublicDefines["FMT_EXPORT"] = "1";
            result.PublicDefines["_CRT_SECURE_NO_WARNINGS"] = "0";

            if (context.Selector.Build == BuildType.Retail)
            {
                result.Kind = ProjectKind.StaticLib;
            }
            else
            {
                result.Kind = ProjectKind.SharedLib;
            }

            return result;
        }
    }
}
