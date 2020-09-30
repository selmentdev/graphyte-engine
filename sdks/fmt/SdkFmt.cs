using Graphyte.Build;

namespace Graphyte
{
    public class SdkFmt : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            if (configuration.Build == BuildType.Retail)
            {
                target.Type = TargetType.StaticLibrary;
            }
            else
            {
                target.Type = TargetType.SharedLibrary;
            }

            target.PublicIncludePaths.Add("sdks/fmt/include");
            target.PublicDefines["FMT_EXCEPTIONS"] = "1";
            target.PublicDefines["FMT_EXPORT"] = "1";
            target.PrivateDefines["_CRT_SECURE_NO_WARNINGS"] = "0";
        }
    }
}
