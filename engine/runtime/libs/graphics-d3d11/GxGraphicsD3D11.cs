using Neobyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxGraphicsD3D11
        : ModuleRules
    {
        public GxGraphicsD3D11(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.Runtime;
            this.Type = ModuleType.SharedLibrary;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PrivateDependencies.Add(typeof(GxGraphics));

            this.PrivateLibraries.AddRange(new[] {
                "dxgi.lib",
                "d3d11.lib",
                "dxguid.lib",
                "user32.lib",
            });
        }
    }
}
