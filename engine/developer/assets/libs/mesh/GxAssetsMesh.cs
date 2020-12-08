using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class GxAssetsMesh : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.SharedLibrary;
            target.PublicIncludePaths.Add("engine/developer/assets/libs/mesh");

            target.AddPublicDependency<GxAssetsBase>();
        }
    }
}
