using System;
using System.Collections.Generic;

namespace GraphyteBuildTool
{
    class Program
    {
        private static VariantSelector[] ValidVariants = new[] {
            new VariantSelector(){
                PlatformType = PlatformType.Windows,
                Architecture = ArchitectureType.X64,
                Build = BuildType.Developer,
                Config = ConfigType.Debug,
            },
            new VariantSelector(){
                PlatformType = PlatformType.Windows,
                Architecture = ArchitectureType.X64,
                Build = BuildType.Retail,
                Config = ConfigType.Release,
            },
        };

        private static IEnumerable<VariantSelector> GetVariants(PlatformType platform)
        {
            foreach (var variant in Program.ValidVariants)
            {
                yield return variant;
            }
        }

        private static void Main(string[] args)
        {
            var os = Environment.OSVersion;
            Console.WriteLine("Graphyte Build Tool");
            Console.WriteLine($@"Operating System: {os.VersionString}");

            var projects = Project.DiscoverProjects();

            foreach (var selector in Program.GetVariants(PlatformType.Windows))
            {
                var context = new ResolveContext(projects, selector);
            }

            foreach (var arg in args)
            {
                Console.WriteLine($@"{arg}");
            }
        }
    }
}
