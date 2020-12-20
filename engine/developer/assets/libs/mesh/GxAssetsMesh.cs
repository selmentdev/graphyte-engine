using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxAssetsMesh
        : ModuleRules
    {
        public GxAssetsMesh(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.SharedLibrary;
            this.Kind = ModuleKind.Developer;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PublicDependencies.Add(typeof(GxAssetsBase));
        }
    }
}
