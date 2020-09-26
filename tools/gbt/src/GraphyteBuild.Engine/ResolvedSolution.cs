using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace Graphyte.Build.Engine
{
    public sealed class ResolvedSolution
    {
        public Solution Solution { get; }
        public ConfigurationContext Context { get; }

        private List<ResolvedTarget> m_Targets = new List<ResolvedTarget>();
        public IReadOnlyList<ResolvedTarget> Targets
        {
            get
            {
                return this.m_Targets;
            }
        }

        public ResolvedSolution(Solution solution, ConfigurationContext context)
        {
            this.Solution = solution;
            this.Context = context;

            foreach (var project in this.Solution.Projects)
            {
                var configuredTarget = new ConfiguredTarget(project);
                this.Solution.PreConfigure(configuredTarget, this.Context);
                project.Configure(configuredTarget, this.Context);
                this.Solution.PostConfigure(configuredTarget, this.Context);

                var resolvedTarget = new ResolvedTarget(this, configuredTarget);
                this.m_Targets.Add(resolvedTarget);
            }

            this.Resolve();
        }

        private void Resolve()
        {
            var callstack = new Stack<ResolvedTarget>();
            foreach (var target in this.Targets)
            {
                target.Resolve(callstack);
            }

            Trace.Assert(callstack.Count == 0);
        }

        public ResolvedTarget FindTargetByProject(string name)
        {
            // Find project with that name
            var found = this.m_Targets.FirstOrDefault(x => x.Target.Project.Name == name);

            if (found == null)
            {
                throw new Exception($@"Cannot resolve project target {name} for solution {this.Solution.Name} in configuration {this.Context}");
            }

            return found;
        }
    }
}
