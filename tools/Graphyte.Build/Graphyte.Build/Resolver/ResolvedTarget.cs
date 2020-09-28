using Graphyte.Build.Extensions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Graphyte.Build.Resolver
{
    [DebuggerDisplay("{" + nameof(GetDebuggerDisplay) + "(),nq}")]
    public sealed partial class ResolvedTarget
    {
        #region Debug View
        private string GetDebuggerDisplay()
        {
            return this.Target.Name;
        }
        #endregion

        #region Properties
        public ResolvedSolution Solution { get; }
        public ConfiguredTarget Target { get; }

        public List<ResolvedTarget> Dependencies { get; } = new List<ResolvedTarget>();
        public List<ResolvedTarget> PrivateDependencies { get; } = new List<ResolvedTarget>();
        public List<string> Libraries { get; } = new List<string>();
        public List<string> PrivateLibraries { get; } = new List<string>();
        public List<string> PrivateIncludePaths { get; } = new List<string>();
        public List<string> IncludePaths { get; } = new List<string>();
        public List<string> PrivateLibraryPaths { get; } = new List<string>();
        public List<string> LibraryPaths { get; } = new List<string>();
        public Dictionary<string, string> PrivateDefines { get; } = new Dictionary<string, string>();
        public Dictionary<string, string> Defines { get; } = new Dictionary<string, string>();
        #endregion

        #region Constructors
        public ResolvedTarget(ResolvedSolution solution, ConfiguredTarget target)
        {
            this.Solution = solution;
            this.Target = target;
        }
        #endregion
    }
}
