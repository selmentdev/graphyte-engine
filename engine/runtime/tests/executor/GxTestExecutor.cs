using Graphyte.Build;

namespace Graphyte
{
    public class GxTestExecutor : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.HeaderLib;

            target.AddPublicDependency<GxLaunch>();
            target.AddPublicDependency<SdkCatch2>();
        }
    }
}
