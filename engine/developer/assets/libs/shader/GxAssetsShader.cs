using Graphyte.Build;

namespace Graphyte
{
    public class GxAssetsShader : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.SharedLibrary;
            target.PublicIncludePaths.Add("engine/developer/assets/libs/shader");

            target.AddPublicDependency<GxAssetsBase>();
        }
    }
}
