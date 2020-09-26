using Graphyte.Build;

namespace Graphyte
{
    public class DevLogFix : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.TestApplication;
            target.Dependencies.AddRange(new[]
            {
                nameof(GxLaunch),
                nameof(GxAssetsMesh),
                nameof(GxAssetsShader),
            });
        }
    }
}
