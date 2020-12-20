using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class DemoApp
        : ModuleRules
    {
        public DemoApp(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.Application;
            this.Kind = ModuleKind.Runtime;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PrivateDependencies.AddRange(
                new[]
                {
                    typeof(GxBase),
                    typeof(GxGraphics),
                    typeof(GxLaunch),
                    typeof(GxRendering),
                    typeof(GxGeometry)
                });
        }
    }
}
