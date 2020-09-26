using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace Graphyte.Build
{
    public static class SolutionProvider
    {
        private static IEnumerable<Type>? DiscoverSolutions()
        {
            var type = typeof(Solution);
            var assembly = Assembly.GetAssembly(type);
            return assembly?.GetTypes()
                .Where(x => x.IsClass && !x.IsAbstract && x.IsSubclassOf(type));
        }

        public static IReadOnlyList<Solution> Solutions { get; }

        static SolutionProvider()
        {
            var types = SolutionProvider.DiscoverSolutions();
            var solutions = new List<Solution>();

            if (types != null)
            {
                foreach (var type in types)
                {
                    var solution = (Solution?)Activator.CreateInstance(type);
                    if (solution != null)
                    {
                        solutions.Add(solution);
                    }
                    else
                    {
                        throw new Exception($@"Cannot create solution {type.Name}");
                    }
                }
            }

            SolutionProvider.Solutions = solutions;
        }
    }
}
