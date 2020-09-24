using GraphyteBuildTool;
using System.Collections.Generic;

namespace Graphyte{
    public class SdkMbedtls : Project
    {
        public override ResolvedProject? Resolve(ResolveContext context)
        {
            var result = new ResolvedProject(this, context);
            result.PublicIncludes.Add("sdks/mbedtls/include");
            result.Kind = ProjectKind.StaticLib;

            if (context.Selector.Architecture == ArchitectureType.X64) {
                result.PrivateDefines["MBEDTLS_HAVE_SSE2"] = "1";
            }

            return result;
        }
    }
}
