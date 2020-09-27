using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct CompilerFamily
        : IEquatable<CompilerFamily>
    {
        private readonly string m_Value;

        public static CompilerFamily Create(string value)
        {
            return new CompilerFamily(value);
        }

        private CompilerFamily(string value)
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

        public override string ToString() => this.m_Value ?? string.Empty;

        public bool Equals([AllowNull] CompilerFamily other)
        {
            return Equals(other.m_Value);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object? obj)
        {
            return obj is CompilerFamily other && this.Equals(other);
        }

        public static bool operator ==(CompilerFamily left, CompilerFamily right)
        {
            return left.Equals(right);
        }

        public static bool operator!=(CompilerFamily left, CompilerFamily right)
        {
            return !(left == right);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }
    }
}
