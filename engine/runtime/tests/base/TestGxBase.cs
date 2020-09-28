using Graphyte.Build;

namespace Graphyte
{
    public class TestGxBase : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.TestApplication;

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxTestExecutor>();
        }
    }
}
