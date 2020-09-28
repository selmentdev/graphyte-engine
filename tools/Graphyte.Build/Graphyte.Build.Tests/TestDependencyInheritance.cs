
using Graphyte.Build.Resolver;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;

namespace Graphyte.Build.Tests
{
    [TestClass]
    public class TestExplicitDependency
    {
        protected struct DependencyVisibility
        {
            public OutputType Type;
            public bool IsPublic;

            public DependencyVisibility(OutputType type, bool isPublic)
            {
                this.Type = type;
                this.IsPublic = isPublic;
            }
        }

        protected abstract class BaseProject : Project
        {
            public DependencyVisibility Visibility { get; set; }
            protected string m_Name = null;

            public override void Configure(ConfiguredTarget target, ConfigurationContext context)
            {
                var name = m_Name;

                target.Type = this.Visibility.Type;

                target.Libraries.Add($@"{name}_library");

                target.Defines[$@"{name}_public_define"] = "1";
                target.IncludePaths.Add($@"{name}_public_include_path");
                target.LibraryPaths.Add($@"{name}_public_library_path");

                target.PrivateDefines[$@"{name}_private_define"] = "1";
                target.PrivateIncludePaths.Add($@"{name}_private_include_path");
                target.PrivateLibraryPaths.Add($@"{name}_private_library_path");
            }
        }

        protected class AppProject : BaseProject
        {
            public AppProject()
            {
                this.m_Name = "app";
            }

            public override void Configure(ConfiguredTarget target, ConfigurationContext context)
            {
                base.Configure(target, context);

                if (this.Visibility.IsPublic)
                {
                    target.AddPublicDependency<DirectDependencyProject>();
                }
                else
                {
                    target.AddPrivateDependency<DirectDependencyProject>();
                }
            }
        }

        protected class DirectDependencyProject : BaseProject
        {
            public DirectDependencyProject()
            {
                this.m_Name = "direct";
            }

            public override void Configure(ConfiguredTarget target, ConfigurationContext context)
            {
                base.Configure(target, context);

                if (this.Visibility.IsPublic)
                {
                    target.AddPublicDependency<IndirectDependencyProject>();
                }
                else
                {
                    target.AddPrivateDependency<IndirectDependencyProject>();
                }
            }
        }

        protected class IndirectDependencyProject : BaseProject
        {
            public IndirectDependencyProject()
            {
                this.m_Name = "leaf";
            }
        }

        protected class SampleSolution : Solution
        {
            public static BuildType DefaultBuildType = BuildType.Developer;
            public static ConfigurationType DefaultConfigurationType = ConfigurationType.Debug;
            public static PlatformType DefaultPlatformType = PlatformType.Windows;
            public static ArchitectureType DefaultArchitectureType = ArchitectureType.Arm64;

            public SampleSolution(
                DependencyVisibility app,
                DependencyVisibility direct,
                DependencyVisibility indirect)
            {
                this.AddBuild(DefaultBuildType);
                this.AddConfiguration(DefaultConfigurationType);
                this.AddTarget(DefaultPlatformType, DefaultArchitectureType);

                this.AddProject(new AppProject()
                {
                    Visibility = app
                });

                this.AddProject(new DirectDependencyProject()
                {
                    Visibility = direct
                });

                this.AddProject(new IndirectDependencyProject()
                {
                    Visibility = indirect
                });
            }
        }

        private ResolvedSolution Resolve(
            DependencyVisibility app,
            DependencyVisibility direct,
            DependencyVisibility indirect)
        {
            var solution = new SampleSolution(app, direct, indirect);
            var context = new ConfigurationContext(
                SampleSolution.DefaultPlatformType,
                SampleSolution.DefaultArchitectureType,
                SampleSolution.DefaultBuildType,
                SampleSolution.DefaultConfigurationType);

            var resolver = new ResolvedSolution(solution, context);

            resolver.Resolve();

            return resolver;
        }

        [TestMethod]
        public void PublicStaticToPublicStatic()
        {
            var solution = Resolve(
                new DependencyVisibility(OutputType.GameApplication, true),
                new DependencyVisibility(OutputType.StaticLib, true),
                new DependencyVisibility(OutputType.StaticLib, true));

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));

            {
                Assert.AreEqual(0, indirect.Dependencies.Count);
                Assert.AreEqual(0, indirect.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(1, direct.Dependencies.Count);
                Assert.AreEqual(0, direct.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(2, app.Dependencies.Count);
                Assert.AreEqual(0, app.PrivateDependencies.Count);
            }
        }

        [TestMethod]
        public void PrivateStaticToPublicStatic()
        {
            var solution = Resolve(
                new DependencyVisibility(OutputType.GameApplication, false),
                new DependencyVisibility(OutputType.StaticLib, true),
                new DependencyVisibility(OutputType.StaticLib, true));

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));

            {
                Assert.AreEqual(0, indirect.Dependencies.Count);
                Assert.AreEqual(0, indirect.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(1, direct.Dependencies.Count);
                Assert.IsNotNull(direct.Dependencies.FirstOrDefault(x => x.Target.Name == nameof(IndirectDependencyProject)));
                Assert.AreEqual(0, direct.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(0, app.Dependencies.Count);
                Assert.AreEqual(2, app.PrivateDependencies.Count);
                Assert.IsNotNull(app.PrivateDependencies.FirstOrDefault(x => x.Target.Name == nameof(DirectDependencyProject)));
                Assert.IsNotNull(app.PrivateDependencies.FirstOrDefault(x => x.Target.Name == nameof(IndirectDependencyProject)));
            }
        }

        [TestMethod]
        public void PublicStaticToPrivateStatic()
        {
            var solution = Resolve(
                new DependencyVisibility(OutputType.GameApplication, true),
                new DependencyVisibility(OutputType.StaticLib, false),
                new DependencyVisibility(OutputType.StaticLib, true));

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));

            {
                Assert.AreEqual(0, indirect.Dependencies.Count);
                Assert.AreEqual(0, indirect.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(0, direct.Dependencies.Count);
                Assert.AreEqual(1, direct.PrivateDependencies.Count);
                Assert.IsNotNull(direct.PrivateDependencies.FirstOrDefault(x => x.Target.Name == nameof(IndirectDependencyProject)));
            }
            {
                Assert.AreEqual(1, app.Dependencies.Count);
                Assert.IsNotNull(app.Dependencies.FirstOrDefault(x => x.Target.Name == nameof(DirectDependencyProject)));

                Assert.AreEqual(1, app.PrivateDependencies.Count);
                Assert.IsNotNull(app.PrivateDependencies.FirstOrDefault(x => x.Target.Name == nameof(IndirectDependencyProject)));
            }
        }

        [TestMethod]
        public void PrivateStaticToPrivateStatic()
        {
            var solution = Resolve(
                new DependencyVisibility(OutputType.GameApplication, false),
                new DependencyVisibility(OutputType.StaticLib, false),
                new DependencyVisibility(OutputType.StaticLib, true));

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));

            {
                Assert.AreEqual(0, indirect.Dependencies.Count);
                Assert.AreEqual(0, indirect.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(0, direct.Dependencies.Count);
                Assert.AreEqual(1, direct.PrivateDependencies.Count);
            }
            {
                Assert.AreEqual(0, app.Dependencies.Count);
                Assert.AreEqual(2, app.PrivateDependencies.Count);
            }
        }

#if false
        [TestMethod]
        public void StaticToShared()
        {
            var solution = Resolve(OutputType.StaticLib, OutputType.SharedLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void StaticToHeader()
        {
            var solution = Resolve(OutputType.StaticLib, OutputType.HeaderLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void StaticToExtern()
        {
            var solution = Resolve(OutputType.StaticLib, OutputType.ExternLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void SharedToStatic()
        {
            var solution = Resolve(OutputType.SharedLib, OutputType.StaticLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void SharedToShared()
        {
            var solution = Resolve(OutputType.SharedLib, OutputType.SharedLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void SharedToHeader()
        {
            var solution = Resolve(OutputType.SharedLib, OutputType.HeaderLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void SharedToExtern()
        {
            var solution = Resolve(OutputType.SharedLib, OutputType.ExternLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void HeaderToStatic()
        {
            var solution = Resolve(OutputType.HeaderLib, OutputType.StaticLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void HeaderToShared()
        {
            var solution = Resolve(OutputType.HeaderLib, OutputType.SharedLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void HeaderToHeader()
        {
            var solution = Resolve(OutputType.HeaderLib, OutputType.HeaderLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void HeaderToExtern()
        {
            var solution = Resolve(OutputType.HeaderLib, OutputType.ExternLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void ExternToStatic()
        {
            var solution = Resolve(OutputType.ExternLib, OutputType.StaticLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void ExternToShared()
        {
            var solution = Resolve(OutputType.ExternLib, OutputType.SharedLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void ExternToHeader()
        {
            var solution = Resolve(OutputType.ExternLib, OutputType.HeaderLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void ExternToExtern()
        {
            var solution = Resolve(OutputType.ExternLib, OutputType.ExternLib);

            var app = solution.FindTargetByProjectName(nameof(AppProject));
            var direct = solution.FindTargetByProjectName(nameof(DirectDependencyProject));
            var indirect = solution.FindTargetByProjectName(nameof(IndirectDependencyProject));
        }

        [TestMethod]
        public void StaticToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.StaticLib, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void StaticToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.StaticLib, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void StaticToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.StaticLib, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void SharedToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.SharedLib, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void SharedToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.SharedLib, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void SharedToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.SharedLib, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void HeaderToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.HeaderLib, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void HeaderToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.HeaderLib, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void HeaderToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.HeaderLib, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void ExternToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.ExternLib, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void ExternToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.ExternLib, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void ExternToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.ExternLib, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void DeveloperToStatic()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.StaticLib);
            });
        }

        [TestMethod]
        public void DeveloperToShared()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.SharedLib);
            });
        }

        [TestMethod]
        public void DeveloperToHeader()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.HeaderLib);
            });
        }

        [TestMethod]
        public void DeveloperToExtern()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.ExternLib);
            });
        }

        [TestMethod]
        public void DeveloperToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void DeveloperToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void DeveloperToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.DeveloperApplication, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void GameToStatic()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.StaticLib);
            });
        }

        [TestMethod]
        public void GameToShared()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.SharedLib);
            });
        }

        [TestMethod]
        public void GameToHeader()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.HeaderLib);
            });
        }

        [TestMethod]
        public void GameToExtern()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.ExternLib);
            });
        }

        [TestMethod]
        public void GameToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void GameToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void GameToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.GameApplication, OutputType.TestApplication);
            });
        }

        [TestMethod]
        public void TestToStatic()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.StaticLib);
            });
        }

        [TestMethod]
        public void TestToShared()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.SharedLib);
            });
        }

        [TestMethod]
        public void TestToHeader()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.HeaderLib);
            });
        }

        [TestMethod]
        public void TestToExtern()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.ExternLib);
            });
        }

        [TestMethod]
        public void TestToDeveloper()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.DeveloperApplication);
            });
        }

        [TestMethod]
        public void TestToGame()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.GameApplication);
            });
        }

        [TestMethod]
        public void TestToTest()
        {
            Assert.ThrowsException<ResolverException>(() =>
            {
                Resolve(OutputType.TestApplication, OutputType.TestApplication);
            });
        }
#endif
    }


    [TestClass]
    public class TestDependencyInheritance
    {
        sealed class SampleSolution : Solution
        {
            public abstract class BaseProject : Project
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    var name = this.GetType().Name;

                    target.Libraries.Add($@"{name}_library");

                    target.Defines[$@"{name}_public_define"] = "1";
                    target.IncludePaths.Add($@"{name}_public_include_path");
                    target.LibraryPaths.Add($@"{name}_public_library_path");

                    target.PrivateDefines[$@"{name}_private_define"] = "1";
                    target.PrivateIncludePaths.Add($@"{name}_private_include_path");
                    target.PrivateLibraryPaths.Add($@"{name}_private_library_path");
                }
            }


            public class App : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Type = OutputType.GameApplication;

                    base.Configure(target, context);
                }
            }

            public class SharedLibrary1 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Type = OutputType.SharedLib;

                    target.Dependencies.Add(nameof(StaticLibrary1));
                    target.Dependencies.Add(nameof(HeaderLibrary1));

                    base.Configure(target, context);
                }
            }

            public class StaticLibrary1 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Type = OutputType.StaticLib;

                    target.Dependencies.Add(nameof(HeaderLibrary1));

                    base.Configure(target, context);
                }
            }

            public class HeaderLibrary1 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(HeaderLibrary2));
                    target.Dependencies.Add(nameof(SharedLibrary2));

                    target.Type = OutputType.HeaderLib;

                    base.Configure(target, context);
                }
            }

            public class HeaderLibrary2 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Dependencies.Add(nameof(StaticLibrary2));

                    target.Type = OutputType.HeaderLib;

                    base.Configure(target, context);
                }
            }

            public class SharedLibrary2 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Type = OutputType.SharedLib;

                    base.Configure(target, context);
                }
            }

            public class StaticLibrary2 : BaseProject
            {
                public override void Configure(ConfiguredTarget target, ConfigurationContext context)
                {
                    target.Type = OutputType.StaticLib;

                    base.Configure(target, context);
                }
            }

            public SampleSolution()
            {
                this.AddBuild(BuildType.Developer);
                this.AddConfiguration(ConfigurationType.Debug);
                this.AddTarget(PlatformType.Windows, ArchitectureType.Arm64);

                this.AddProject(new App());
                this.AddProject(new SharedLibrary1());
                this.AddProject(new SharedLibrary2());
                this.AddProject(new StaticLibrary1());
                this.AddProject(new StaticLibrary2());
                this.AddProject(new HeaderLibrary1());
                this.AddProject(new HeaderLibrary2());
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

            resolver.Resolve();

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.SharedLibrary2));

                Assert.AreEqual(0, project.Dependencies.Count);

                Assert.AreEqual(1, project.Libraries.Count);
                Assert.IsTrue(project.Libraries.Contains("SharedLibrary2_library"));

                Assert.AreEqual(1, project.Defines.Count);
                Assert.AreEqual("1", project.Defines["SharedLibrary2_public_define"]);

                Assert.AreEqual(1, project.IncludePaths.Count);
                Assert.IsTrue(project.IncludePaths.Contains("SharedLibrary2_public_include_path"));

                Assert.AreEqual(1, project.LibraryPaths.Count);
                Assert.IsTrue(project.LibraryPaths.Contains("SharedLibrary2_public_library_path"));

                Assert.AreEqual(1, project.PrivateDefines.Count);
                Assert.AreEqual("1", project.PrivateDefines["SharedLibrary2_private_define"]);

                Assert.AreEqual(1, project.PrivateIncludePaths.Count);
                Assert.IsTrue(project.PrivateIncludePaths.Contains("SharedLibrary2_private_include_path"));

                Assert.AreEqual(1, project.PrivateLibraryPaths.Count);
                Assert.IsTrue(project.PrivateLibraryPaths.Contains("SharedLibrary2_private_library_path"));
            }
            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.StaticLibrary2));

                Assert.AreEqual(0, project.Dependencies.Count);

                Assert.AreEqual(1, project.Libraries.Count);
                Assert.IsTrue(project.Libraries.Contains("StaticLibrary2_library"));

                Assert.AreEqual(1, project.Defines.Count);
                Assert.AreEqual("1", project.Defines["StaticLibrary2_public_define"]);

                Assert.AreEqual(1, project.IncludePaths.Count);
                Assert.IsTrue(project.IncludePaths.Contains("StaticLibrary2_public_include_path"));

                Assert.AreEqual(1, project.LibraryPaths.Count);
                Assert.IsTrue(project.LibraryPaths.Contains("StaticLibrary2_public_library_path"));

                Assert.AreEqual(1, project.PrivateDefines.Count);
                Assert.AreEqual("1", project.PrivateDefines["StaticLibrary2_private_define"]);

                Assert.AreEqual(1, project.PrivateIncludePaths.Count);
                Assert.IsTrue(project.PrivateIncludePaths.Contains("StaticLibrary2_private_include_path"));

                Assert.AreEqual(1, project.PrivateLibraryPaths.Count);
                Assert.IsTrue(project.PrivateLibraryPaths.Contains("StaticLibrary2_private_library_path"));
            }

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.HeaderLibrary2));

                Assert.AreEqual(project.Defines.Count, 1);
                Assert.AreEqual(project.Defines["USE_HEADER_LIBRARY_2_PUBLIC"], "1");

                Assert.AreEqual(project.PrivateDefines.Count, 1);
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_2_PRIVATE"], "1");
            }

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.HeaderLibrary1));

                Assert.AreEqual(project.Defines.Count, 2);
                Assert.AreEqual(project.Defines["USE_HEADER_LIBRARY_1_PUBLIC"], "1");
                Assert.AreEqual(project.Defines["USE_HEADER_LIBRARY_2_PUBLIC"], "1");

                Assert.AreEqual(project.PrivateDefines.Count, 2);
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_1_PRIVATE"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_2_PRIVATE"], "1");
            }

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.StaticLibrary1));

                Assert.AreEqual(project.Defines.Count, 1);
                Assert.AreEqual(project.Defines["USE_STATIC_LIBRARY_PUBLIC"], "1");

                Assert.AreEqual(project.PrivateDefines.Count, 2);
                Assert.AreEqual(project.PrivateDefines["USE_STATIC_LIBRARY_PRIVATE"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_1_PUBLIC"], "1");

                //Assert.AreEqual(project.Libraries.Count, 2);
                //Assert.IsTrue(project.Libraries.Contains("static.lib"));
                //Assert.IsTrue(project.Libraries.Contains("header.lib"));
            }

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.SharedLibrary1));

                Assert.AreEqual(project.Defines.Count, 1);
                Assert.AreEqual(project.Defines["USE_SHARED_LIBRARY_PUBLIC"], "1");

                Assert.AreEqual(project.PrivateDefines.Count, 4);
                Assert.AreEqual(project.PrivateDefines["USE_SHARED_LIBRARY_PRIVATE"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_STATIC_LIBRARY_PUBLIC"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_1_PUBLIC"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_HEADER_LIBRARY_2_PUBLIC"], "1");

                //Assert.AreEqual(project.Libraries.Count, 3);
                //Assert.IsTrue(project.Libraries.Contains("shared.lib"));
                //Assert.IsTrue(project.Libraries.Contains("static.lib"));
                //Assert.IsTrue(project.Libraries.Contains("header.lib"));
            }

            {
                var project = resolver.FindTargetByProjectName(nameof(SampleSolution.App));

                Assert.AreEqual(project.Defines.Count, 1);
                Assert.AreEqual(project.Defines["USE_APP_LIBRARY_PUBLIC"], "1");

                Assert.AreEqual(project.PrivateDefines.Count, 2);
                Assert.AreEqual(project.PrivateDefines["USE_APP_LIBRARY_PRIVATE"], "1");
                Assert.AreEqual(project.PrivateDefines["USE_SHARED_LIBRARY_PUBLIC"], "1");

                //Assert.AreEqual(project.Libraries.Count, 1);
                //Assert.IsTrue(project.Libraries.Contains("app.lib"));
            }
        }
    }
}
