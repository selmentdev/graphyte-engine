using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxLaunch
        : ModuleRules
    {
        public GxLaunch(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.ExternLibrary;
            this.Kind = ModuleKind.Runtime;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PublicDependencies.AddRange(new[]
            {
                typeof(GxBase),
                typeof(GxGeometry),
                typeof(GxGraphics),
                typeof(GxGraphicsD3D11),
            });

            if (target.Descriptor.Platform == TargetPlatform.UniversalWindows)
            {
                this.PublicLibraries.Add("WindowsApp.lib");
            }
            else if (target.Descriptor.Platform ==TargetPlatform.Windows)
            {
                this.PublicLibraries.AddRange(new[]
                {
                    "Mincore.lib",
                    "user32.lib",
                    "shell32.lib",
                });
            }
        }
    }
}
