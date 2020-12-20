using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class SdkVulkanVma
        : ModuleRules
    {
        public SdkVulkanVma(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.StaticLibrary;
            this.Kind = ModuleKind.ThirdParty;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "include"));
        }
    }
}
