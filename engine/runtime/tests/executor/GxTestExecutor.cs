using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class GxTestExecutor : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.HeaderLibrary;

            target.AddPublicDependency<GxLaunch>();
            target.AddPublicDependency<SdkCatch2>();
        }
    }
}
