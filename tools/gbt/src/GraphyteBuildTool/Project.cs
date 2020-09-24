using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Reflection;

namespace GraphyteBuildTool
{
    public abstract class Project : IComparable<Project>
    {
        public string Name
        {
            get
            {
                return this.GetType().Name;
            }
        }

        public int CompareTo([AllowNull] Project other)
        {
            if (other == null) {
                return 1;
            }
            return this.Name.CompareTo(other.Name);
        }

        public abstract ResolvedProject? Resolve(ResolveContext context);

        private static List<Type>? GetProjectTypes()
        {
            var type = typeof(Project);
            var assembly = Assembly.GetAssembly(type);
            return assembly?.GetTypes()
                           ?.Where(x => x.IsClass && x.IsSubclassOf(type) && !x.IsAbstract)
                           ?.ToList();
        }

        public static List<Project> DiscoverProjects()
        {
            var projects = Project.GetProjectTypes();
            var result = new List<Project>();

            if (projects != null)
            {
                foreach (var project in projects) {
                    var instance = (Project?)Activator.CreateInstance(project);
                    if (instance != null) {
                        result.Add(instance);
                    }
                }
            }

            return result;
        }
    }
}
