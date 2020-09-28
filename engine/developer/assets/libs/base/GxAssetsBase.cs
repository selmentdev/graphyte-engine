using Graphyte.Build;

namespace Graphyte
{
    public class GxAssetsBase : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.SharedLib;
            target.IncludePaths.Add("engine/developer/assets/libs/base");

            target.AddPublicDependency<GxBase>();
        }
    }
}
