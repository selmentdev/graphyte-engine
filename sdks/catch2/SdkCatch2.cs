using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class SdkCatch2
        : ModuleRules
    {
        public SdkCatch2(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.ExternLibrary;
            this.Kind = ModuleKind.ThirdParty;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));
        }
    }
}
