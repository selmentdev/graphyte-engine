using Graphyte.Build;

namespace Graphyte
{
    public class DevLogFix : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.TestApplication;

            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxAssetsMesh>();
            target.AddPrivateDependency<GxAssetsShader>();
        }
    }
}
