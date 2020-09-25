using System.Collections.Generic;

namespace GraphyteBuildTool.Projects
{
    public class ProjectDefinition
    {
        public ProjectDefinition(Project project)
        {
            this.Name = project.Name;
        }

        public string Name { get; set; }
        public ProjectKind Kind { get; set; } = ProjectKind.SharedLib;

        public List<string> PublicIncludes { get; private set; } = new List<string>();
        public List<string> PrivateIncludes { get; private set; } = new List<string>();

        public List<string> Libraries { get; private set; } = new List<string>();
        public List<string> Dependencies { get; private set; } = new List<string>();

        public Dictionary<string, string> PublicDefines { get; private set; } = new Dictionary<string, string>();
        public Dictionary<string, string> PrivateDefines { get; private set; } = new Dictionary<string, string>();
    }
}
