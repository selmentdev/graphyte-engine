using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class SdkLz4
        : ModuleRules
    {
        public SdkLz4(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.StaticLibrary;
            this.Language = ModuleLanguage.C;
            this.Kind = ModuleKind.ThirdParty;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));
        }
    }
}
