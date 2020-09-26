using Graphyte.Build;

namespace Graphyte
{
    public class SdkCatch2 : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.HeaderLib;
            target.IncludePaths.Add("sdks/catch2/include");
        }
    }
}
