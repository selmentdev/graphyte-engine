using Graphyte.Build.Engine;
using Graphyte.Build.Platforms.Windows;
using System;
using System.Linq;

namespace Graphyte.Build.Application
{
    class Program
    {
        private static readonly Version CurrentVersion = new Version(1, 0, 0, 0);

        private static void Main(string[] args)
        {
            Console.WriteLine($@"Graphyte Build {Program.CurrentVersion}");
            var os = Environment.OSVersion;

            Console.WriteLine($@"Operating System: {os.VersionString}");
            Console.WriteLine($@"Discovering solutions...");

            var solutions = SolutionProvider.Solutions;

            var context = new ConfigurationContext(
                PlatformType.Windows,
                ArchitectureType.X64,
                BuildType.Developer,
                ConfigurationType.Release);

            var resolvedSolution = new ResolvedSolution(solutions.First(), context);
        }
    }
}
