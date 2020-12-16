using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxAssetsBase
        : ModuleRules
    {
        public GxAssetsBase(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.Developer;
            this.Type = ModuleType.SharedLibrary;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateDependencies.Add(typeof(GxBase));

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));
        }
    }
}
