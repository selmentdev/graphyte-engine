using Graphyte.Build.Extensions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Graphyte.Build.Resolver
{
    public sealed partial class ResolvedTarget
    {
        #region Resolving
        public bool IsResolved { get; private set; } = false;
        public bool IsInheritable => this.Target.IsInheritable;
        #endregion

        private void ValidateDependencyCycle(Stack<ResolvedTarget> callstack)
        {
            if (callstack.Contains(this))
            {
                var message = new StringBuilder();
                message.AppendLine($@"Cycle in dependent module {this.Target.Name} found");

                foreach (var call in callstack)
                {
                    message.AppendLine($@"- required by {call.Target.Name}");
                }

                throw new ResolverException(message.ToString());
            }
        }

        public void Resolve(Stack<ResolvedTarget> callstack)
        {
            this.ValidateDependencyCycle(callstack);

            callstack.Push(this);

            if (this.IsResolved == false)
            {
                Console.WriteLine($@"{this.Target.Name}: Resolving target");
                //Console.Indent();

                this.IsResolved = true;

                this.ImportProperties();

                foreach (var dependency in this.Dependencies)
                {
                    dependency.Resolve(callstack);
                }

                foreach (var dependency in this.PrivateDependencies)
                {
                    dependency.Resolve(callstack);
                }


                this.ResolveDependencies();

                this.ResolveProperties();

                //Console.Unindent();
            }

            callstack.Pop();
        }

        /// <summary>
        /// Imports properties and dependencies from configured target.
        /// </summary>
        private void ImportProperties()
        {
            Console.WriteLine($@"{this.Target.Name}: Importing properties");
            //Console.Indent();

            this.Dependencies.AddRange(this.Target.Dependencies.Select(this.Solution.FindTargetByProjectName));
            this.PrivateDependencies.AddRange(this.Target.PrivateDependencies.Select(this.Solution.FindTargetByProjectName));

            this.Defines.Import(this.Target.Defines);
            this.PrivateDefines.Import(this.Target.PrivateDefines);

            this.IncludePaths.Import(this.Target.IncludePaths);
            this.PrivateIncludePaths.Import(this.Target.PrivateIncludePaths);

            this.Libraries.Import(this.Target.Libraries);
            this.PrivateLibraries.Import(this.Target.PrivateLibraries);

            this.LibraryPaths.Import(this.Target.LibraryPaths);
            this.PrivateLibraryPaths.Import(this.Target.PrivateLibraryPaths);

            //Console.Unindent();
        }

        private void ResolveDependencies()
        {
            Console.WriteLine($@"{this.Target.Name}: Started resolving dependencies");
            //Console.Indent();

            foreach (var dependency in this.PrivateDependencies.ToArray())
            {
                this.ResolvePrivateDependency(dependency);
            }

            foreach (var dependency in this.Dependencies.ToArray())
            {
                this.ResolvePublicDependency(dependency);
            }

            //Console.Unindent();
        }

        /// <summary>
        /// Imports specified public dependency.
        /// </summary>
        /// <param name="dependency">A public dependency</param>
        private void ResolvePublicDependency(ResolvedTarget dependency)
        {
            Console.WriteLine($@"{this.Target.Name}: resolve public {dependency.Target.Name}");
            //Console.Indent();
            Console.WriteLine($@"- {this.Target.Type} <= {dependency.Target.Type}");

            if (!dependency.Target.Type.IsLibrary())
            {
                //
                // Only library can be consumed as public dependency.
                //

                throw new ResolverException($@"Target {this.Target.Name} of type {this.Target.Type} cannot be used as dependency");
            }


            //
            // Consume public dependencies of library.
            //

            this.Dependencies.Import(dependency.Dependencies);

            if (dependency.Target.IsInheritable)
            {
                //
                // Consume private dependencies of static/header only libraries.
                //

                this.PrivateDependencies.Import(dependency.PrivateDependencies);
            }

            //Console.Unindent();
        }

        private void ResolvePrivateDependency(ResolvedTarget dependency)
        {
            Console.WriteLine($@"{this.Target.Name}: resolve private {dependency.Target.Name}");
            //Console.Indent();
            Console.WriteLine($@"- {this.Target.Type} <= {dependency.Target.Type}");

            if (!dependency.Target.Type.IsLibrary())
            {
                //
                // Only library can be consumed as private dependency.
                //

                throw new ResolverException($@"Target {this.Target.Name} of type {this.Target.Type} cannot be used as dependency");
            }


            //
            // Import public dependencies as private.
            //

            this.PrivateDependencies.Import(dependency.Dependencies);

            if (dependency.IsInheritable)
            {
                //
                // Dependency is inheritable. Import private dependencies as private.
                //
                //

                this.PrivateDependencies.Import(dependency.PrivateDependencies);
            }

            //Console.Unindent();
        }

        private void ResolveProperties()
        {
            foreach (var dependency in this.Dependencies)
            {
                this.ResolvePublicDependencyProperties(dependency);
            }

            foreach (var dependency in this.PrivateDependencies)
            {
                this.ResolvePrivateDependencyProperties(dependency);
            }
        }

        private void ResolvePublicDependencyProperties(ResolvedTarget dependency)
        {
        }

        private void ResolvePrivateDependencyProperties(ResolvedTarget dependency)
        {
        }

#if false
        private void ResolveDependency(ResolvedTarget dependency)
        {
            if (dependency.Target.Type == OutputType.StaticLib)
            {
                // - consumer requires dependencies
                this.Libraries.Import(dependency.Libraries);

                // - is already compiled.
                //this.PrivateIncludePaths.Import(dependency.PrivateIncludePaths);

                // - consumer requires dependencies
                this.PrivateIncludePaths.Import(dependency.IncludePaths);

                // - consumer requires dependencies
                this.PrivateLibraryPaths.Import(dependency.PrivateLibraryPaths);

                // - consumer requires dependencies
                this.PrivateLibraryPaths.Import(dependency.LibraryPaths);

                // - is already compiled
                //this.PrivateDefines.Import(dependency.PrivateDefines);

                // - consumer requires dependencies
                this.PrivateDefines.Import(dependency.Defines);
            }
            else if (dependency.Target.Type == OutputType.SharedLib)
            {
                // - is already linked
                //this.Libraries.Import(dependency.Libraries);

                // - is already compiled
                //this.PrivateIncludePaths.Import(dependency.PrivateIncludePaths);

                // - consumer requires dependencies
                this.PrivateIncludePaths.Import(dependency.IncludePaths);
                // - is already compiled
                //this.PrivateLibraryPaths.Import(dependency.PrivateLibraryPaths);

                // - consumer requires dependencies
                this.PrivateLibraryPaths.Import(dependency.LibraryPaths);

                // - is already compiled
                //this.PrivateDefines.Import(dependency.PrivateDefines);

                // - consumer requires dependencies
                this.PrivateDefines.Import(dependency.Defines);
            }
            else if (dependency.Target.Type == OutputType.ExternLib)
            {
                // - consumer requires dependencies
                this.Libraries.Import(dependency.Libraries);

                // - is already compiled
                //this.PrivateIncludePaths.Import(dependency.PrivateIncludePaths);

                // - consumer requires dependencies
                this.PrivateIncludePaths.Import(dependency.IncludePaths);

                // - is already compiled
                //this.PrivateLibraryPaths.Import(dependency.PrivateLibraryPaths);

                // - consumer requires dependencies
                this.PrivateLibraryPaths.Import(dependency.LibraryPaths);

                // - is already compiled
                //this.PrivateDefines.Import(dependency.PrivateDefines);

                // - consumer requires dependencies
                this.PrivateDefines.Import(dependency.Defines);
            }
            else if (dependency.Target.Type == OutputType.HeaderLib)
            {
                if (this.Target.Type == OutputType.HeaderLib)
                {
                    // At resolving stage, chains of dependant header libraries are broken away.
                }
                else
                {
                    // - consumer requires dependencies
                    this.Libraries.Import(dependency.Libraries);

                    // - consumer requires dependencies
                    this.PrivateIncludePaths.Import(dependency.PrivateIncludePaths);

                    // - consumer requires dependencies
                    this.PrivateIncludePaths.Import(dependency.IncludePaths);

                    // - consumer requires dependencies
                    this.PrivateLibraryPaths.Import(dependency.PrivateLibraryPaths);

                    // - consumer requires dependencies
                    this.PrivateLibraryPaths.Import(dependency.LibraryPaths);

                    // - consumer requires dependencies
                    this.PrivateDefines.Import(dependency.PrivateDefines);

                    // - consumer requires dependencies
                    this.PrivateDefines.Import(dependency.Defines);
                }
            }
            else
            {
                throw new ResolverException($@"Project {dependency.Target.Name} ({dependency.Target.Type}) cannot be a dependency to {this.Target.Name} ({this.Target.Type}) ");
            }
        }
#endif
    }
}
