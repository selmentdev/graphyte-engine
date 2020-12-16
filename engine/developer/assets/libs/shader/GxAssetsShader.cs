using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxAssetsShader
        : ModuleRules
    {
        public GxAssetsShader(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.Developer;
            this.Type = ModuleType.SharedLibrary;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PublicDependencies.Add(typeof(GxAssetsBase));
        }
    }
}
