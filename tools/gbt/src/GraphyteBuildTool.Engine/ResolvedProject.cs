using System.Collections.Generic;

namespace GraphyteBuildTool.Projects
{
    public sealed class ResolvedProject
    {
        public ProjectDefinition Definition { get; }

        public List<ResolvedProject> Dependencies { get; } = new List<ResolvedProject>();

        public List<ResolvedProject> InheritedDependencies { get; internal set; } = new List<ResolvedProject>();

        public ResolvedProject(ProjectDefinition definition) {
            this.Definition = definition;
        }
    }
}
