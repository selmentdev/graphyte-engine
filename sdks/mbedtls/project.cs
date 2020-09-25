using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte{
    public class SdkMbedtls : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.Kind = ProjectKind.StaticLib;
            result.PublicIncludes.Add("sdks/mbedtls/include");

            if (configuration.Architecture == ArchitectureType.X64) {
                result.PrivateDefines["MBEDTLS_HAVE_SSE2"] = "1";
            }

            return result;
        }
    }
}
