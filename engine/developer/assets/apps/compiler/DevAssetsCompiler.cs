using Graphyte.Build;

namespace Graphyte
{
    public class DevAssetsCompiler : Project
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.DeveloperApplication;
            target.Dependencies.AddRange(new[]
            {
                nameof(GxLaunch),
                nameof(GxAssetsMesh),
                nameof(GxAssetsShader),
            });
        }
    }
}
