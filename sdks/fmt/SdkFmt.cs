using Neobyte.Build.Framework;
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

            this.Type = (target.LinkType == TargetLinkType.Monolithic)
                ? ModuleType.StaticLibrary
                : ModuleType.SharedLibrary;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));

            this.PublicDefines.Add("FMT_EXCEPTIONS=1");
            this.PrivateDefines.Add("_CRT_SECURE_NO_WARNINGS=0");

            if (this.Type == ModuleType.SharedLibrary)
            {
                this.PrivateDefines.Add("FMT_EXPORT=1");
                this.InterfaceDefines.Add("FMT_SHARED=1");
            }
        }
    }
}
