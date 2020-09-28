using Graphyte.Build.Resolver;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Json;

namespace Graphyte.Build.Dump
{
    public static class DumpSolution
    {
        public static void DumpToFile(ResolvedSolution solution, string path)
        {
            using var file = System.IO.File.CreateText(path);

            foreach(var target in solution.Targets)
            {
                DumpTarget(file, target);
            }
        }

        private static void DumpTarget(StreamWriter file, ResolvedTarget target)
        {
            file.WriteLine($@"Target: name = `{target.Target.Name}`, type = `{target.Target.Type}`");

            foreach (var dependency in target.Dependencies)
            {
                file.WriteLine($@"- public dependency:    `{dependency.Target.Name}`");
            }

            foreach (var dependency in target.PrivateDependencies)
            {
                file.WriteLine($@"- private dependency:   `{dependency.Target.Name}`");
            }

            foreach (var item in target.Defines)
            {
                file.WriteLine($@"- public define:        `{item.Key}` = `{item.Value}`");
            }

            foreach (var item in target.PrivateDefines)
            {
                file.WriteLine($@"- public define:        `{item.Key}` = `{item.Value}`");
            }

            foreach (var item in target.Libraries)
            {
                file.WriteLine($@"- public library:       `{item}`");
            }

            foreach (var item in target.PrivateLibraries)
            {
                file.WriteLine($@"- private library:      `{item}`");
            }

            foreach (var item in target.IncludePaths)
            {
                file.WriteLine($@"- public include path:  `{item}`");
            }

            foreach (var item in target.PrivateIncludePaths)
            {
                file.WriteLine($@"- private include path: `{item}`");
            }

            foreach (var item in target.LibraryPaths)
            {
                file.WriteLine($@"- public library path:  `{item}`");
            }

            foreach (var item in target.PrivateLibraryPaths)
            {
                file.WriteLine($@"- private library path: `{item}`");
            }
        }
    }
}
