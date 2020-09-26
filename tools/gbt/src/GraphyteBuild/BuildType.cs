using System;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.InteropServices;

namespace Graphyte.Build
{
    /// <summary>
    /// Represents build type.
    /// </summary>
    public readonly struct BuildType
        : IEquatable<BuildType>
    {
        #region Common build types
        /// <summary>
        /// Developer build - used by programmers.
        /// </summary>
        public static BuildType Developer = new BuildType("Developer");

        /// <summary>
        /// Testing build - used by QA.
        /// </summary>
        public static BuildType Testing = new BuildType("Testing");

        /// <summary>
        /// Retail build - final shippable build.
        /// </summary>
        public static BuildType Retail = new BuildType("Retail");
        #endregion

        /// <summary>
        /// Internal value.
        /// </summary>
        private readonly string m_Name;

        /// <summary>
        /// Creates new custom build type.
        /// </summary>
        /// <param name="name">A build type name.</param>
        /// <returns>The build type.</returns>
        public static BuildType Create(string name)
        {
            return new BuildType(name);
        }

        /// <summary>
        /// Creates new instance of BuildType.
        /// </summary>
        /// <param name="name">A build type name.</param>
        private BuildType(string name)
        {
            if (name == null)
            {
                throw new ArgumentNullException(nameof(name));
            }

            if (name.Length == 0)
            {
                throw new ArgumentOutOfRangeException(nameof(name));
            }

            this.m_Name = name;
        }

        public override string ToString() => this.m_Name ?? string.Empty;

        public bool Equals([AllowNull] BuildType other)
        {
            return Equals(other.m_Name);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Name, value, StringComparison.Ordinal);
        }

        public override bool Equals(object? obj)
        {
            return obj is BuildType other && this.Equals(other);
        }

        public static bool operator ==(BuildType left, BuildType right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(BuildType left, BuildType right)
        {
            return !(left == right);
        }


        public override int GetHashCode()
        {
            return this.m_Name.GetHashCode();
        }
    }
}
