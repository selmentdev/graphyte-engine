using System;

namespace Graphyte.Build
{
    public sealed class CompilerFamily
    {
        public string Name { get; }

        public CompilerFamily(string name)
        {
            this.Name = name;
        }

        public override string ToString() => this.Name;

        public static bool operator ==(CompilerFamily lhs, CompilerFamily rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
            {
                return true;
            }

            if ((object)lhs == null || (object)rhs == null)
            {
                return false;
            }

            return lhs.Equals(rhs);
        }

        public static bool operator !=(CompilerFamily lhs, CompilerFamily rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object? obj)
        {
            return obj is CompilerFamily other &&
                   this.Name == other.Name;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(this.Name);
        }
    }
}
