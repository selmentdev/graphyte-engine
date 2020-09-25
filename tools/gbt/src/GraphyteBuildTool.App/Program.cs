using System;
using System.Collections.Generic;
using System.IO;
using GraphyteBuildTool.Engine;
using GraphyteBuildTool.Platforms;
using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.App
{
    class Program
    {
        //     private static VariantSelector[] ValidVariants = new[] {
        //         new VariantSelector(){
        //             Platform = PlatformType.Windows,
        //             Architecture = ArchitectureType.X64,
        //             Build = BuildType.Developer,
        //             Config = ConfigType.Debug,
        //         },
        //         new VariantSelector(){
        //             Platform = PlatformType.Windows,
        //             Architecture = ArchitectureType.X64,
        //             Build = BuildType.Retail,
        //             Config = ConfigType.Release,
        //         },
        //     };

        //     private static IEnumerable<VariantSelector> GetVariants(PlatformType platform)
        //     {
        //         foreach (var variant in Program.ValidVariants)
        //         {
        //             yield return variant;
        //         }
        //     }

        private static void Main(string[] args)
        {
            var os = Environment.OSVersion;
            Console.WriteLine("Graphyte Build Tool");
            Console.WriteLine($@"Operating System: {os.VersionString}");
            Console.WriteLine($@"Discovering projects...");

            foreach (var project in Solution.Projects)
            {
                Console.WriteLine($@"Project `{project.Name}`");
            }

            var configuration = new Configuration(
                            PlatformType.Windows,
                            ArchitectureType.X64,
                            BuildType.Retail,
                            ConfigType.Release);

            var context = new ResolveContext(configuration, Solution.Projects);

            foreach (var project in context.Projects)
            {
                Console.WriteLine($@"Definition: `{project.Definition.Name}`");
            }

            var platform = PlatformProvider.Platforms[configuration.Platform];

            foreach (var project in context.Projects)
            {
                Console.WriteLine($@"FileName: `{platform.GetTargetFileName(project.Definition.Kind, project.Definition.Name)}`");
            }

            foreach (var project in context.Projects)
            {
                Console.WriteLine($@"Dependencies: `{project.Definition.Name}`");
                foreach (var dependency in project.Dependencies) {
                    Console.WriteLine($@"- explicit: {dependency.Definition.Name}");
                }
                foreach (var dependency in project.InheritedDependencies) {
                    Console.WriteLine($@"- inherited: {dependency.Definition.Name}");
                }
            }

            // var generator = new PlaintextStructureGenerator();
            // var projects = Project.DiscoverProjects();

            // foreach (var selector in Program.GetVariants(PlatformType.Windows))
            // {
            //     var context = new ResolveContext(projects, selector);

            //     using (FileStream fs = File.Create($@"debug_{selector.Platform}_{selector.Architecture}_{selector.Build}_{selector.Config}.bff"))
            //     {
            //         generator.Generate(fs, context);
            //     }
            // }

            foreach (var arg in args)
            {
                Console.WriteLine($@"{arg}");
            }
        }
    }
}
