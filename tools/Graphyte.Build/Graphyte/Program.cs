using System;
using Graphyte.Build;
using Graphyte.Build.Platforms.Windows;
using Graphyte.Build.Resolver;

namespace Graphyte
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine($@"Location: {WindowsSdk.Location}");

            foreach (var version in WindowsSdk.Availablle)
            {
                Console.WriteLine($@"Version: {version}");
            }

            foreach (var vs in Graphyte.Build.Toolchains.VisualStudio.VisualStudioProvider.Locations)
            {
                Console.WriteLine($@"VS ({vs.Name}, {vs.Version}, {vs.Location})");
            }

            foreach (var build in new[] { BuildType.Developer, BuildType.Retail })
            {
                var solution = new MainSolution();
                var context = new ConfigurationContext(
                    PlatformType.Windows,
                    ArchitectureType.X64,
                    build,
                    ConfigurationType.Release);
                var resolved = new ResolvedSolution(solution, context);
                resolved.Resolve();

                Graphyte.Build.Dump.DumpSolution.DumpToFile(resolved, $@"solution_{build}.txt");
            }
        }
    }
}
