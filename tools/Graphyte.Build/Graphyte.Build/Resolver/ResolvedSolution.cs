using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace Graphyte.Build.Resolver
{
    public sealed class ResolvedSolution
    {
        public Solution Solution { get; }
        public ConfigurationContext Context { get; }

        private readonly List<ResolvedTarget> m_Targets = new List<ResolvedTarget>();
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
        }

        public void Resolve()
        {
            var context = this.Context;

            foreach (var project in this.Solution.Projects)
            {
                var configuredTarget = new ConfiguredTarget(project);

                // Give chance to configure project initially by solution
                this.Solution.PreConfigure(configuredTarget, context);

                project.Configure(configuredTarget, context);

                this.Solution.PostConfigure(configuredTarget, context);

                var resolvedTarget = new ResolvedTarget(this, configuredTarget);
                this.m_Targets.Add(resolvedTarget);
            }

            var callstack = new Stack<ResolvedTarget>();

            foreach (var target in this.Targets)
            {
                target.Resolve(callstack);
            }

            if (callstack.Count != 0)
            {
                throw new InvalidOperationException("Internal resolving error");
            }
        }

        public ResolvedTarget FindTargetByProjectName(string name)
        {
            var found = this.m_Targets.FirstOrDefault(x => x.Target.Project.Name == name);

            if (found == null)
            {
                throw new ResolverException(
                    $@"Cannot resolve project target {name} for solution {this.Solution.Name} in configuration {this.Context}");
            }

            return found;
        }
    }
}
