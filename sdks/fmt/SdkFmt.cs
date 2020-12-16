using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class SdkFmt
        : ModuleRules
    {
        public SdkFmt(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.ThirdParty;
            this.Language = ModuleLanguage.CPlusPlus;

            this.Type = target.LinkType == TargetLinkType.Monolithic
                ? ModuleType.StaticLibrary
                : ModuleType.SharedLibrary;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));

            this.PublicDefines.AddRange(new[] {
                "FMT_EXCEPTIONS=1",
                "FMT_EXPORT=1",
                "_CRT_SECURE_NO_WARNINGS=0",
            });
        }
    }
}
