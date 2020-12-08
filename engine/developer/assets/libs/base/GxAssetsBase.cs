using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class GxAssetsBase : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.SharedLibrary;
            target.PublicIncludePaths.Add("engine/developer/assets/libs/base");

            target.AddPublicDependency<GxBase>();
        }
    }
}
