using Graphyte.Build;

namespace Graphyte
{
    public class SdkLz4 : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.StaticLib;
            target.IncludePaths.Add("sdks/lz4/include");
        }
    }
}
