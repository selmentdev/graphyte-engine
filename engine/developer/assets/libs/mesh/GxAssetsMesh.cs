using Graphyte.Build;

namespace Graphyte
{
    public class GxAssetsMesh : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.SharedLibrary;
            target.PublicIncludePaths.Add("engine/developer/assets/libs/mesh");

            target.AddPublicDependency<GxAssetsBase>();
        }
    }
}
