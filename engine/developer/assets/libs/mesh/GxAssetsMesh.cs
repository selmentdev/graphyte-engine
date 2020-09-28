using Graphyte.Build;

namespace Graphyte
{
    public class GxAssetsMesh : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.SharedLib;
            target.IncludePaths.Add("engine/developer/assets/libs/mesh");

            target.AddPublicDependency<GxAssetsBase>();
        }
    }
}
