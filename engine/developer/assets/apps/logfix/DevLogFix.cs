using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class DevLogFix : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.Application;

            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxAssetsMesh>();
            target.AddPrivateDependency<GxAssetsShader>();
        }
    }
}
