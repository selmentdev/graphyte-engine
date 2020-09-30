using Graphyte.Build;

namespace Graphyte
{
    public class DevLogFix : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.Application;

            target.AddPrivateDependency<GxLaunch>();
            target.AddPrivateDependency<GxAssetsMesh>();
            target.AddPrivateDependency<GxAssetsShader>();
        }
    }
}
