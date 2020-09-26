using Graphyte.Build;

namespace Graphyte
{
    public class GxTestExecutor : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.HeaderLib;
            target.Dependencies.AddRange(new[] {
                nameof(GxLaunch),
                nameof(SdkCatch2),
            });
        }
    }
}
