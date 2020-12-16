using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxRendering
        : GraphyteModule
    {
        public GxRendering(TargetRules target)
            : base(target)
        {
            this.Kind = ModuleKind.Runtime;
            this.Type = ModuleType.SharedLibrary;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));

            this.PublicDependencies.Add(typeof(GxGraphics));
        }
    }
}
