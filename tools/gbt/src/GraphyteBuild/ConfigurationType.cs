using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct ConfigurationType
        : IEquatable<ConfigurationType>
    {
        public static ConfigurationType Release = new ConfigurationType("Release");
        public static ConfigurationType Profile = new ConfigurationType("Profile");
        public static ConfigurationType Checked = new ConfigurationType("Checked");
        public static ConfigurationType Debug = new ConfigurationType("Debug");


        private readonly string m_Value;

        public static ConfigurationType Create(string value)
        {
            return new ConfigurationType(value);
        }

        private ConfigurationType(string value)
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

        public bool Equals([AllowNull] ConfigurationType other)
        {
            return Equals(other.m_Value);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object? obj)
        {
            return obj is ConfigurationType other && this.Equals(other);
        }

        public static bool operator ==(ConfigurationType left, ConfigurationType right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(ConfigurationType left, ConfigurationType right)
        {
            return !(left == right);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }
    }
}
