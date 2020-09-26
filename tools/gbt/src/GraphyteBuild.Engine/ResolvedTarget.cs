using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Graphyte.Build.Engine
{
    /// <summary>
    /// Represents resolved target.
    /// </summary>
    [DebuggerDisplay("{" + nameof(GetDebuggerDisplay) + "(),nq}")]
    public sealed class ResolvedTarget
    {
        #region Properties
        public ResolvedSolution Solution { get; }

        /// <summary>
        /// Original configured target.
        /// </summary>
        public ConfiguredTarget Target { get; }
        #endregion

        #region Dependencies
        /// <summary>
        /// List of resolved dependencies
        /// </summary>
        public List<ResolvedTarget> Dependencies { get; } = new List<ResolvedTarget>();
        #endregion

        #region Properties

        public List<string> Libraries { get; } = new List<string>();

        public List<string> PrivateIncludePaths { get; } = new List<string>();

        public List<string> IncludePaths { get; } = new List<string>();

        public List<string> PrivateLibraryPaths { get; } = new List<string>();

        public List<string> LibraryPaths { get; } = new List<string>();

        public Dictionary<string, string> PrivateDefines { get; } = new Dictionary<string, string>();

        public Dictionary<string, string> Defines { get; } = new Dictionary<string, string>();

        #endregion


        #region Constructors
        /// <summary>
        /// Create new instance of resolved target.
        /// </summary>
        /// <param name="target">A target to resolve.</param>
        public ResolvedTarget(ResolvedSolution solution, ConfiguredTarget target)
        {
            this.Solution = solution;
            this.Target = target;
        }
        #endregion

        #region Resolving
        public bool IsResolved { get; private set; } = false;

        public void Resolve(Stack<ResolvedTarget> callstack)
        {
            if (callstack.Contains(this))
            {
                var message = new StringBuilder();
                message.AppendLine($@"Cycle in dependent module {this.Target.Name} found");

                foreach (var call in callstack)
                {
                    message.AppendLine($@"- required by {call.Target.Name}");
                }

                throw new Exception(message.ToString());
            }

            callstack.Push(this);

            if (this.IsResolved == false)
            {
                // Mark target as being resolved
                this.IsResolved = true;

                // Find and recursively resolve dependent targets
                foreach (var dependency in this.Target.Dependencies)
                {
                    var target = this.Solution.FindTargetByProject(dependency);
                    target.Resolve(callstack);

                    this.Dependencies.Add(target);
                }

                this.ResolveDependencies();
                this.ResolveProperties();
            }

            callstack.Pop();
        }

        private void ResolveDependencies()
        {
            var inheritable = this.Dependencies
                .Where(x => x.Target.Type.IsInheritableDependency())
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
            #region Public Properties

            foreach (var item in this.Target.Defines.Concat(this.Dependencies.SelectMany(x => x.Defines)))
            {
                this.Defines[item.Key] = item.Value;
            }

            foreach (var item in this.Target.IncludePaths.Concat(this.Dependencies.SelectMany(x => x.IncludePaths)))
            {
                if (!this.IncludePaths.Contains(item))
                {
                    this.IncludePaths.Add(item);
                }
            }

            foreach (var item in this.Target.LibraryPaths.Concat(this.Dependencies.SelectMany(x => x.LibraryPaths)))
            {
                if (!this.LibraryPaths.Contains(item))
                {
                    this.LibraryPaths.Add(item);
                }
            }

            #endregion

            #region Inheritable Properties

            foreach (var item in this.Target.Libraries.Concat(this.Dependencies.Where(x => x.Target.Type.IsInheritableDependency()).SelectMany(x => x.Libraries)))
            {
                if (!this.Libraries.Contains(item))
                {
                    this.Libraries.Add(item);
                }
            }

            #endregion

            #region Private Properties

            foreach (var item in this.Target.PrivateDefines)
            {
                this.PrivateDefines[item.Key] = item.Value;
            }

            foreach (var item in this.Target.PrivateIncludePaths)
            {
                if (!this.PrivateIncludePaths.Contains(item))
                {
                    this.PrivateIncludePaths.Add(item);
                }
            }

            foreach (var item in this.Target.PrivateLibraryPaths)
            {
                if (!this.PrivateLibraryPaths.Contains(item))
                {
                    this.PrivateLibraryPaths.Add(item);
                }
            }

            #endregion

            this.Print();
        }

        private void Print()
        {
            Console.WriteLine($@"{this.Target.Name}");

            foreach (var item in this.Dependencies)
            {
                Console.WriteLine($@"- requires({item.Target.Name})");
            }

            foreach (var item in this.Libraries)
            {
                Console.WriteLine($@"- links({item})");
            }

            foreach (var item in this.Defines)
            {
                Console.WriteLine($@"- define({item.Key}, {item.Value})");
            }

            foreach (var item in this.PrivateDefines)
            {
                Console.WriteLine($@"- define-private({item.Key}, {item.Value})");
            }

            foreach (var item in this.IncludePaths)
            {
                Console.WriteLine($@"- path-include ""{item}""");
            }

            foreach (var item in this.PrivateIncludePaths)
            {
                Console.WriteLine($@"- path-include-private ""{item}""");
            }

            foreach (var item in this.LibraryPaths)
            {
                Console.WriteLine($@"- path-library ""{item}""");
            }

            foreach (var item in this.PrivateLibraryPaths)
            {
                Console.WriteLine($@"- path-library-private ""{item}""");
            }
        }

        #endregion

        private string GetDebuggerDisplay()
        {
            return this.Target.Name;
        }
    }
}
