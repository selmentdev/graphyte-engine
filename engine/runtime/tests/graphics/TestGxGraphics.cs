using Neobyte.Build.Framework;

namespace Graphyte
{
    [ModuleRules]
    public class TestGxGraphics
        : ModuleRules
    {
        public TestGxGraphics(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.Application;
            this.Kind = ModuleKind.Test;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateDependencies.AddRange(new[]
            {
                typeof(GxBase),
                typeof(GxTestExecutor),
            });
        }
    }
}
