using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxGeometry
        : ModuleRules
    {
        public GxGeometry(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.SharedLibrary;
            this.Kind = ModuleKind.Runtime;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PublicDependencies.Add(typeof(GxBase));
        }
    }
}
