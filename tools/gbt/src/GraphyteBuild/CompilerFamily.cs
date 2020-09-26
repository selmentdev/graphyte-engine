using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct CompilerFamily
        : IEquatable<CompilerFamily>
    {
        private readonly string m_Id;

        public static CompilerFamily Create(string id)
        {
            return new CompilerFamily(id);
        }

        private CompilerFamily(string id)
        {
            if (id == null)
            {
                throw new ArgumentNullException(nameof(id));
            }

            if (id.Length == 0)
            {
                throw new ArgumentOutOfRangeException(nameof(id));
            }

            this.m_Id = id;
        }

        public override string ToString() => this.m_Id ?? string.Empty;

        public bool Equals([AllowNull] CompilerFamily other)
        {
            return Equals(other.m_Id);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Id, value, StringComparison.Ordinal);
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
            return this.m_Id.GetHashCode();
        }
    }
}
