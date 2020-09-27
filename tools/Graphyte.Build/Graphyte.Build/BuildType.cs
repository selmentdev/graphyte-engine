using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct BuildType
        : IEquatable<BuildType>
    {
        public static BuildType Developer = new BuildType("Developer");
        public static BuildType Testing = new BuildType("Testing");
        public static BuildType Retail = new BuildType("Retail");

        private readonly string m_Value;

        private BuildType(string value)
        {
            if (value == null)
            {
                throw new ArgumentNullException(nameof(value));
            }

            if (value.Length == 0)
            {
                throw new ArgumentOutOfRangeException(nameof(value));
            }

            this.m_Value = value;
        }

        public static BuildType Create(string value)
        {
            return new BuildType(value);
        }

        public override string ToString()
        {
            return this.m_Value ?? string.Empty;
        }

        public bool Equals([AllowNull] BuildType other)
        {
            return this.Equals(other.m_Value);
        }

        private bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object obj)
        {
            return obj is BuildType other && this.Equals(other);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }

        public static bool operator==(BuildType left, BuildType right)
        {
            return left.Equals(right);
        }

        public static bool operator!=(BuildType left, BuildType right)
        {
            return !(left == right);
        }
    }
}
