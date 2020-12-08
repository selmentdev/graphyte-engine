using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class TestGxEntities : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.Application;

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxTestExecutor>();
        }
    }
}
