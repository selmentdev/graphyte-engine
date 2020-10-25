using Graphyte.Build;

namespace Graphyte
{
    public class TestGxGraphics : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.Application;

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxTestExecutor>();
        }
    }
}
