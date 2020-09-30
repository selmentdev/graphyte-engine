using System;
using Graphyte.Build;
using Graphyte.Build.Resolving;

namespace Graphyte
{
    class Program
    {
        static void Main()
        {
            foreach (var build in new[] { BuildType.Developer, BuildType.Retail })
            {
                var solution = new MainSolution();
                var context = new Context(
                    PlatformType.Windows,
                    ArchitectureType.X64,
                    build,
                    ConfigurationType.Release);
                var resolved = new ResolvedSolution(solution, context);
                resolved.Resolve();

                Graphyte.Build.Dump.DumpResolvedSolution.SaveToFile($@"solution_{build}.json", resolved);
            }
        }
    }
}
