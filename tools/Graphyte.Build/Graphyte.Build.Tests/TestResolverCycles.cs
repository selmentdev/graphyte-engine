using Graphyte.Build.Resolver;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Graphyte.Build.Tests
{
    [TestClass]
    public class TestResolverCycles
    {
        sealed class SolutionWithCycles : Solution
        {
            // This sample has cyclic dependency graph:
            //
            // /--> A ----> B -\
            // |       \--> C ---> D --\
            // \-----------------------/
            //
            // B requires A
            // C requires A
            // D requires B
            // D requires C
            // A requires D

            class ProjectA : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(ProjectD));
                }
            }

            class ProjectB : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(ProjectA));
                }
            }

            class ProjectC : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(ProjectA));
                }
            }

            class ProjectD : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(ProjectA));
                    target.Dependencies.Add(nameof(ProjectB));
                }
            }

            public SolutionWithCycles()
            {
                this.AddBuild(BuildType.Developer);
                this.AddConfiguration(ConfigurationType.Debug);
                this.AddTarget(PlatformType.Windows, ArchitectureType.Arm64);

                this.AddProject(new ProjectA());
                this.AddProject(new ProjectB());
                this.AddProject(new ProjectC());
                this.AddProject(new ProjectD());
            }
        }

        [TestMethod]
        public void CheckCyclesInSolution()
        {
            var solution = new SolutionWithCycles();
            var context = new ConfigurationContext(
                solution.TargetTypes.First(),
                solution.BuildTypes.First(),
                solution.ConfigurationTypes.First());

            var resolver = new ResolvedSolution(solution, context);

            Assert.ThrowsException<ResolverException>(() => { resolver.Resolve(); });
        }
    }
}
