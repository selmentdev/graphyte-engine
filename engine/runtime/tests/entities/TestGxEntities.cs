using Graphyte.Build;

namespace Graphyte
{
    public class TestGxEntities : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.Application;

            target.AddPrivateDependency<GxBase>();
            target.AddPrivateDependency<GxTestExecutor>();
        }
    }
}
