using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public sealed class ConfiguredTarget
    {
        public Target SourceTarget { get; }
        public OutputType Type { get; set; }
        public string Name { get; set; }

        public List<string> Dependencies { get; } = new List<string>();
        public List<string> PrivateDependencies { get; } = new List<string>();
        public List<string> Libraries { get; } = new List<string>();
        public List<string> PrivateLibraries { get; } = new List<string>();
        public List<string> IncludePaths { get; } = new List<string>();
        public List<string> PrivateIncludePaths { get; } = new List<string>();
        public List<string> LibraryPaths { get; } = new List<string>();
        public List<string> PrivateLibraryPaths { get; } = new List<string>();
        public Dictionary<string, string> Defines { get; } = new Dictionary<string, string>();
        public Dictionary<string, string> PrivateDefines { get; set; } = new Dictionary<string, string>();

        public bool IsInheritable => this.Type.IsInheritableDependency();

        public ConfiguredTarget(Target project)
        {
            this.SourceTarget = project;
            this.Name = project.Name;
        }

        public void AddPublicDependency<T>()
            where T : Target
        {
            this.Dependencies.Add(typeof(T).Name);
        }

        public void AddPrivateDependency<T>()
            where T : Target
        {
            this.PrivateDependencies.Add(typeof(T).Name);
        }
    }
}
