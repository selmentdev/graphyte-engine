using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class SdkVulkanVma : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.StaticLibrary;

            target.PublicIncludePaths.Add("sdks/vulkanvma/include");
        }
    }
}
