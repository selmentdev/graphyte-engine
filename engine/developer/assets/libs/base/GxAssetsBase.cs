using Graphyte.Build;

namespace Graphyte
{
    public class GxAssetsBase : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.SharedLibrary;
            target.PublicIncludePaths.Add("engine/developer/assets/libs/base");

            target.AddPublicDependency<GxBase>();
        }
    }
}
