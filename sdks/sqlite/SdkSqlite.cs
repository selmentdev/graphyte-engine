using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public  class SdkSqlite
        : ModuleRules
    {
        public SdkSqlite(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.StaticLibrary;
            this.Kind = ModuleKind.ThirdParty;
            this.Language = ModuleLanguage.C;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));
        }
    }
}
