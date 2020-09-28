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
                Debug.WriteLine($@"{this.Target.Name}: Resolving target");
                Debug.Indent();

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

                Debug.Unindent();
            }

            callstack.Pop();
        }

        /// <summary>
        /// Imports properties and dependencies from configured target.
        /// </summary>
        private void ImportProperties()
        {
            Debug.WriteLine($@"{this.Target.Name}: Importing properties");
            Debug.Indent();

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

            Debug.Unindent();
        }

        private void ResolveDependencies()
        {
            Debug.WriteLine($@"{this.Target.Name}: Started resolving dependencies");
            Debug.Indent();

            foreach (var dependency in this.PrivateDependencies.ToArray())
            {
                this.ResolvePrivateDependency(dependency);
            }

            foreach (var dependency in this.Dependencies.ToArray())
            {
                this.ResolvePublicDependency(dependency);
            }

            Debug.Unindent();
        }

        private void ResolvePublicDependency(ResolvedTarget dependency)
        {
            Debug.WriteLine($@"{this.Target.Name}: resolve public {dependency.Target.Name}");
            Debug.Indent();
            Debug.WriteLine($@"- {this.Target.Type} <= {dependency.Target.Type}");

            Debug.Unindent();
        }

        private void ResolvePrivateDependency(ResolvedTarget dependency)
        {
            Debug.WriteLine($@"{this.Target.Name}: resolve private {dependency.Target.Name}");
            Debug.Indent();
            Debug.WriteLine($@"- {this.Target.Type} <= {dependency.Target.Type}");



            Debug.Unindent();
        }

#if false
        private void ResolveDependencies()
        {
            var inheritable = this.Dependencies
                .Where(x => x.IsInheritable)
                .SelectMany(x => x.Dependencies)
                .ToArray();

            foreach (var dependency in inheritable)
            {
                if (!this.Dependencies.Contains(dependency))
                {
                    this.Dependencies.Add(dependency);
                }
            }
        }

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
