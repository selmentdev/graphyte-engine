using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.Projects
{
    public static class Solution
    {
        public static IReadOnlyList<Project> Projects { get; private set; }
        private static List<Type>? GetProjectTypes()
        {
            var type = typeof(Project);
            var assembly = Assembly.GetAssembly(type);
            return assembly?.GetTypes()?.Where(x => x.IsClass && x.IsSubclassOf(type) && !x.IsAbstract)?.ToList();
        }

        static Solution()
        {
            var types = Solution.GetProjectTypes();

            var projects = new List<Project>();

            if (types != null)
            {
                foreach (var type in types)
                {
                    var project = (Project?)Activator.CreateInstance(type);
                    if (project != null)
                    {
                        projects.Add(project);
                    }
                    else
                    {
                        throw new Exception($@"Cannot create instance of type {type}");
                    }
                }
            }

            Solution.Projects = projects;
        }
    }
}
