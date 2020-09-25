using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class SdkFmt : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);
            result.PublicIncludes.Add("sdks/fmt/include");
            result.PublicDefines["FMT_EXCEPTIONS"] = "1";
            result.PublicDefines["FMT_EXPORT"] = "1";
            result.PrivateDefines["_CRT_SECURE_NO_WARNINGS"] = "0";

            if (configuration.Build == BuildType.Retail)
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
