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


        private readonly string m_Id;

        public static ConfigurationType Create(string id)
        {
            return new ConfigurationType(id);
        }

        private ConfigurationType(string id)
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

        public bool Equals([AllowNull] ConfigurationType other)
        {
            return Equals(other.m_Id);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Id, value, StringComparison.Ordinal);
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
            return this.m_Id.GetHashCode();
        }
    }
}
