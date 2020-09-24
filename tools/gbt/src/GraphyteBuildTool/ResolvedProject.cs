using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;

namespace GraphyteBuildTool
{
    public class ResolvedProject : IComparable<ResolvedProject>
    {
        public Project SourceProject { get; private set; }

        public VariantSelector Selector { get; private set; }
        public string Name
        {
            get
            {
                return this.SourceProject.Name;
            }
        }

        public ProjectKind Kind { get; set; }
        public List<string> PublicIncludes { get; set; } = new List<string>();
        public List<string> PrivateIncludes { get; set; } = new List<string>();
        public List<string> LibraryDirectories { get; set; } = new List<string>();
        public Dictionary<string, string> PublicDefines { get; set; } = new Dictionary<string, string>();
        public Dictionary<string, string> PrivateDefines { get; set; } = new Dictionary<string, string>();
        public List<string> Libraries { get; set; } = new List<string>();
        public List<string> Dependencies { get; set; } = new List<string>();

        internal SortedSet<ResolvedProject> ResolvedImmediateDependencies { get; private set; } = new SortedSet<ResolvedProject>();
        internal SortedSet<ResolvedProject> ResolvedInheritedDependencies { get; private set; } = new SortedSet<ResolvedProject>();

        public List<string> ResolvedPublicIncludes { get; private set; } = new List<string>();
        public List<string> ResolvedPrivateIncludes { get; private set; } = new List<string>();
        public List<string> ResolvedLibraries { get; private set; } = new List<string>();
        public Dictionary<string, string> ResolvedPublicDefines {get; private set; } = new Dictionary<string, string>();
        public Dictionary<string, string> ResolvedPrivateDefines {get; private set; } = new Dictionary<string, string>();

        public ResolvedProject(Project source, ResolveContext context)
        {
            this.SourceProject = source;
            this.Selector = context.Selector;
        }

        internal void ImplResolveImmediateDependencies(ResolveContext context)
        {
            // Resolve just immediate dependencies - this process is linear as we do inherited dependencies later
            var dependencies = new SortedSet<ResolvedProject>();

            // Take dependencies from default selector
            foreach (var dependency in this.Dependencies)
            {
                dependencies.Add(context.RequireProject(dependency));
            }

            this.ResolvedImmediateDependencies = dependencies;
        }

        internal void ImplResolveInheritedDependencies(ResolveContext context)
        {
            var visited = new SortedSet<ResolvedProject>();
            var remaining = new SortedSet<ResolvedProject>();

            foreach (var current in this.ResolvedImmediateDependencies)
            {
                remaining.Add(current);
            }

            while (remaining.Count > 0)
            {
                var current = remaining.First();
                remaining.Remove(current);

                if (visited.Add(current))
                {
                    // project was not visited
                    if (current.Kind == ProjectKind.StaticLib)
                    {
                        // static lib populates its dependencies
                        foreach (var dependency in current.ResolvedImmediateDependencies)
                        {
                            remaining.Add(dependency);
                        }
                    }
                }
            }

            this.ResolvedInheritedDependencies = visited;
        }

        internal void ImplResolveProperties(ResolveContext context)
        {
            // Resolve all properties

            // public includes
            var allPublicIncludes = this.PublicIncludes.Concat(this.ResolvedInheritedDependencies.SelectMany(x => x.PublicIncludes));
            foreach (var include in allPublicIncludes) {
                if (!this.ResolvedPublicIncludes.Contains(include)) {
                    this.ResolvedPublicIncludes.Add(include);
                }
            }
            var allPrivateIncludes = this.PrivateIncludes;
            foreach (var include in allPrivateIncludes) {
                if (!this.ResolvedPrivateIncludes.Contains(include)) {
                    this.ResolvedPrivateIncludes.Add(include);
                }
            }

            var allLibraries = this.Libraries.Concat(this.ResolvedInheritedDependencies.SelectMany(x => x.Libraries));
            foreach (var include in allLibraries) {
                if (!this.ResolvedLibraries.Contains(include)) {
                    this.ResolvedLibraries.Add(include);
                }
            }

            var allPublicDefines = this.PublicDefines.Concat(this.ResolvedInheritedDependencies.SelectMany( x => x.PublicDefines));
            foreach (var define in allPublicDefines) {
                if (!this.ResolvedPublicDefines.ContainsKey(define.Key)) {
                    this.ResolvedPublicDefines.Add(define.Key, define.Value);
                }
            }

            var allPrivateDefines = this.PrivateDefines;
            foreach (var define in allPrivateDefines) {
                if (!this.ResolvedPrivateDefines.ContainsKey(define.Key)) {
                    this.ResolvedPrivateDefines.Add(define.Key, define.Value);
                }
            }
        }

        public string? ExportSymbol
        {
            get
            {
                if (this.Kind == ProjectKind.SharedLib)
                {
                    return $@"module_export_{this.Name}";
                }

                return null;

            }
        }

        public int CompareTo([AllowNull] ResolvedProject other)
        {
            if (other == null)
            {
                return 1;
            }
            return this.SourceProject.CompareTo(other.SourceProject);
        }
    }
}
