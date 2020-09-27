using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct CompilerFamily
        : IEquatable<CompilerFamily>
    {
        private readonly string m_Value;

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

        public static CompilerFamily Create(string value)
        {
            return new CompilerFamily(value);
        }

        public override string ToString()
        {
            return this.m_Value ?? string.Empty;
        }

        public bool Equals([AllowNull] CompilerFamily other)
        {
            return this.Equals(other.m_Value);
        }

        private bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object obj)
        {
            return obj is CompilerFamily other && this.Equals(other);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }

        public static bool operator ==(CompilerFamily left, CompilerFamily right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(CompilerFamily left, CompilerFamily right)
        {
            return !(left == right);
        }
    }
}
