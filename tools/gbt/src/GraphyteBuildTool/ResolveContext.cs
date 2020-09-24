using System;
using System.Collections.Generic;
using System.Linq;

namespace GraphyteBuildTool
{
    public sealed class ResolveContext
    {
        public VariantSelector Selector { get; private set; }
        public List<ResolvedProject> Projects { get; private set; }

        public ResolvedProject RequireProject(string name)
        {
            var found = this.Projects.FirstOrDefault(x => x.SourceProject.Name == name);

            if (found == null)
            {
                throw new Exception($@"Cannot resolve project {name}");
            }

            return found;
        }

        public ResolveContext(IEnumerable<Project> projects, VariantSelector selector)
        {
            this.Selector = selector;
            this.Projects = new List<ResolvedProject>();

            foreach (var project in projects)
            {
                var resolved = project.Resolve(this);
                if (resolved != null)
                {
                    this.Projects.Add(resolved);
                }
            }

            foreach (var project in this.Projects)
            {
                project.ImplResolveImmediateDependencies(this);
            }

            foreach (var project in this.Projects)
            {
                project.ImplResolveInheritedDependencies(this);
            }

            foreach (var project in this.Projects)
            {
                project.ImplResolveProperties(this);
            }

            foreach (var project in this.Projects)
            {
                Console.WriteLine($@"proj: {project.SourceProject.Name} = {project.Kind}");

                foreach (var dependency in project.Dependencies)
                {
                    Console.WriteLine($@"- deps-explicit: {dependency}");
                }

                foreach (var dependency in project.ResolvedInheritedDependencies)
                {
                    Console.WriteLine($@"- deps-inherited: {dependency.SourceProject.Name} = {dependency.Kind}");
                }

                foreach (var item in project.ResolvedPublicIncludes) {
                    Console.WriteLine($@"- pub-include: {item}");
                }

                foreach (var item in project.ResolvedLibraries) {
                    Console.WriteLine($@"- link-library: {item}");
                }

                foreach (var define in project.ResolvedPublicDefines) {
                    Console.WriteLine($@"- pub-define: `{define.Key}` = `{define.Value}`");
                }

                foreach (var define in project.ResolvedPrivateDefines) {
                    Console.WriteLine($@"- prv-define: `{define.Key}` = `{define.Value}`");
                }
            }
        }
    }
}
