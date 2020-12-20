using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxGraphicsVulkan
        : ModuleRules
    {
        public GxGraphicsVulkan(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.SharedLibrary;
            this.Kind = ModuleKind.Runtime;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PrivateDependencies.Add(typeof(GxGraphics));
        }
    }
}
