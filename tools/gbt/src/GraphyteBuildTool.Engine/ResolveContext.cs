using System;
using System.Collections.Generic;
using System.Linq;
using GraphyteBuildTool.Projects;

namespace GraphyteBuildTool.Engine
{
    public sealed class ResolveContext
    {
        public Configuration Configuration { get; }
        public IReadOnlyList<ResolvedProject> Projects { get; }

        public ResolveContext(Configuration configuration, IEnumerable<Project> projects)
        {
            // Setup configuration
            this.Configuration = configuration;

            // Get project definitions for this configuration
            var definitions = new List<ResolvedProject>();

            foreach (var project in projects)
            {
                var definition = project.GetDefinition(configuration);
                if (definition != null)
                {
                    definitions.Add(new ResolvedProject(definition));
                }
            }

            this.Projects = definitions;

            // First, resolve all immediate dependencies - it is required in second phase
            foreach (var project in this.Projects)
            {
                this.ResolveImmediateDependencies(project);
            }

            // Then, follow header and static libs and get their dependencies as well
            foreach (var project in this.Projects)
            {
                this.ResolveInheritedDependencies(project);
            }
        }

        private ResolvedProject Require(string name)
        {
            var found = this.Projects.FirstOrDefault(x => x.Definition.Name == name);

            if (found == null)
            {
                throw new Exception($@"Cannot resolve project {name}");
            }
            return found;
        }

        private void ResolveImmediateDependencies(ResolvedProject project)
        {
            foreach (var dependency in project.Definition.Dependencies)
            {
                project.Dependencies.Add(this.Require(dependency));
            }
        }

        private void ResolveInheritedDependencies(ResolvedProject project)
        {
            var visited = new List<ResolvedProject>();
            var remaining = new List<ResolvedProject>();

            foreach (var current in project.Dependencies)
            {
                remaining.Add(current);
            }

            while (remaining.Count > 0)
            {
                var current = remaining.First();
                remaining.Remove(current);

                if (!visited.Contains(current))
                {
                    visited.Add(current);

                    if (current.Definition.Kind == ProjectKind.StaticLib || current.Definition.Kind == ProjectKind.HeaderLib) {
                        foreach (var dependency in current.Dependencies) {
                            remaining.Add(dependency);
                        }
                    }
                }
            }

            project.InheritedDependencies = visited;
        }
    }
}
