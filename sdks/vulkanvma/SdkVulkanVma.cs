using Graphyte.Build;

namespace Graphyte
{
    public class SdkVulkanVma : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.StaticLib;

            target.IncludePaths.Add("sdks/vulkanvma/include");
        }
    }
}
