using Neobyte.Build.Framework;

namespace Graphyte
{
    [ModuleRules]
    public class DevAssetsCompiler
        : ModuleRules
    {
        public DevAssetsCompiler(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.Developer;
            this.Type = ModuleType.Application;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateDependencies.AddRange(new[] {
                typeof(GxLaunch),
                typeof(GxAssetsMesh),
                typeof(GxAssetsShader),
            });
        }
    }
}
