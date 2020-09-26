using Graphyte.Build;

namespace Graphyte
{
    public class TestGxEntities : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.TestApplication;
            target.Dependencies.AddRange(new[]
            {
                nameof(GxBase),
                nameof(GxTestExecutor),
            });
        }
    }
}
