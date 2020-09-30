using Graphyte.Build;

namespace Graphyte
{
    public class GxTestExecutor : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.HeaderLibrary;

            target.AddPublicDependency<GxLaunch>();
            target.AddPublicDependency<SdkCatch2>();
        }
    }
}
