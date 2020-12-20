using Neobyte.Build.Framework;

namespace Graphyte
{
    [ModuleRules]
    public class GxTestExecutor
        : ModuleRules
    {
        public GxTestExecutor(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.ExternLibrary;
            this.Kind = ModuleKind.Developer;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicDependencies.AddRange(new[]
            {
                typeof(GxLaunch),
                typeof(SdkCatch2),
            });
        }
    }
}
