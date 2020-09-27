using Graphyte.Build.Extensions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Graphyte.Build.Resolver
{
    [DebuggerDisplay("{" + nameof(GetDebuggerDisplay) + "(),nq}")]
    public sealed class ResolvedTarget
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
        public List<string> Libraries { get; } = new List<string>();
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

        #region Resolving
        public bool IsResolved { get; private set; } = false;
        public bool IsInheritable => this.Target.IsInheritable;

        public void Resolve(Stack<ResolvedTarget> callstack)
        {
            ResolverCycleDetected(callstack);

            callstack.Push(this);

            if (this.IsResolved == false)
            {
                // Mark target as being resolved
                this.IsResolved = true;

                // Find and recursively resolve dependent targets
                foreach (var dependency in this.Target.Dependencies)
                {
                    var target = this.Solution.FindTargetByProjectName(dependency);
                    target.Resolve(callstack);

                    this.Dependencies.Add(target);
                }

                this.ResolveDependencies();
                this.ResolveProperties();
            }

            callstack.Pop();
        }

        private void ResolverCycleDetected(Stack<ResolvedTarget> callstack)
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

        private void ResolveProperties()
        {
            // Import properties from source
            foreach (var item in this.Target.Defines)
            {
                this.Defines[item.Key] = item.Value;
            }

            foreach (var item in this.Target.PrivateDefines)
            {
                this.PrivateDefines[item.Key] = item.Value;
            }

            foreach (var item in this.Target.Libraries)
            {
                this.Libraries.Import(item);
            }

            foreach (var item in this.Target.IncludePaths)
            {
                this.IncludePaths.Import(item);
            }

            foreach (var item in this.Target.PrivateIncludePaths)
            {
                this.PrivateIncludePaths.Import(item);
            }

            foreach (var item in this.Target.LibraryPaths)
            {
                this.LibraryPaths.Import(item);
            }

            foreach (var item in this.Target.PrivateLibraryPaths)
            {
                this.PrivateLibraryPaths.Import(item);
            }

            foreach (var dependency in this.Dependencies)
            {
                this.ResolveDependency(dependency);
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
        #endregion
    }
}
