using Graphyte.Build;

namespace Graphyte
{
    public class SdkFmt : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            if (configuration.Build == BuildType.Retail)
            {
                target.Type = OutputType.StaticLib;
            }
            else
            {
                target.Type = OutputType.SharedLib;
            }

            target.IncludePaths.Add("sdks/fmt/include");
            target.Defines["FMT_EXCEPTIONS"] = "1";
            target.Defines["FMT_EXPORT"] = "1";
            target.PrivateDefines["_CRT_SECURE_NO_WARNINGS"] = "0";
        }
    }
}
