using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Graphyte.Build.Resolver;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Graphyte.Build.Tests
{
    [TestClass]
    public class TestResolverMissingDependencies
    {
        sealed class SampleSolution : Solution
        {
            class App : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(SharedLibrary));
                }
            }

            class SharedLibrary : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                }
            }

            public SampleSolution()
            {
                this.AddBuild(BuildType.Developer);
                this.AddConfiguration(ConfigurationType.Debug);
                this.AddTarget(PlatformType.Windows, ArchitectureType.Arm64);

                this.AddProject(new App());
            }
        }

        [TestMethod]
        public void TestInheritance()
        {
            var solution = new SampleSolution();
            var context = new ConfigurationContext(
                solution.TargetTypes.First(),
                solution.BuildTypes.First(),
                solution.ConfigurationTypes.First());

            var resolver = new ResolvedSolution(solution, context);

            Assert.ThrowsException<ResolverException>(() => { resolver.Resolve(); });
        }
    }
}
