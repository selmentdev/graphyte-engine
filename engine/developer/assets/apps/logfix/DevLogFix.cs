using Neobyte.Build.Framework;

namespace Graphyte
{
    [ModuleRules]
    public class DevLogFix
        : ModuleRules
    {
        public DevLogFix(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.Application;
            this.Kind = ModuleKind.Developer;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateDependencies.AddRange(new[] {
                typeof(GxLaunch),
                typeof(GxAssetsMesh),
                typeof(GxAssetsShader),
            });
        }
    }
}
