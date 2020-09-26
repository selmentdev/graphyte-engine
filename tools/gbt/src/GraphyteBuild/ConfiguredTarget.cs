using System.Collections.Generic;

namespace Graphyte.Build
{
    public sealed class ConfiguredTarget
    {
        public Project Project { get; }

        public OutputType Type { get; set; }

        public string Name { get; set; }

        public CompilerFamily? Compiler { get; set; }

        /// <summary>
        /// Names of imported dependent projects.
        /// </summary>
        public List<string> Dependencies { get; } = new List<string>();

        public List<string> Libraries { get; } = new List<string>();

        public List<string> PrivateIncludePaths { get; } = new List<string>();

        public List<string> IncludePaths { get; } = new List<string>();

        public List<string> PrivateLibraryPaths { get; } = new List<string>();

        public List<string> LibraryPaths { get; } = new List<string>();

        public Dictionary<string, string> PrivateDefines { get; } = new Dictionary<string, string>();

        public Dictionary<string, string> Defines { get; } = new Dictionary<string, string>();

        public ConfiguredTarget(Project project)
        {
            this.Project = project;
            this.Name = project.Name;
        }
    }
}
