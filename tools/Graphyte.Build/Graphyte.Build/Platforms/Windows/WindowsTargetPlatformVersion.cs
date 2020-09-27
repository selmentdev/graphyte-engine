using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build
{
    public readonly struct WindowsTargetPlatformVersion
        : IEquatable<WindowsTargetPlatformVersion>
    {
        public static WindowsTargetPlatformVersion V10_0_18362_0 = new WindowsTargetPlatformVersion("10.0.18362.0");
        public static WindowsTargetPlatformVersion V10_0_19041_0 = new WindowsTargetPlatformVersion("10.0.19041.0");

        private readonly string m_Value;

        private WindowsTargetPlatformVersion(string value)
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

        public static WindowsTargetPlatformVersion Create(string value)
        {
            return new WindowsTargetPlatformVersion(value);
        }

        public static WindowsTargetPlatformVersion Create(Version value)
        {
            return new WindowsTargetPlatformVersion(value.ToString());
        }

        public override string ToString()
        {
            return this.m_Value ?? string.Empty;
        }

        public Version ToVersion()
        {
            return Version.Parse(this.m_Value);
        }

        public bool Equals([AllowNull] WindowsTargetPlatformVersion other)
        {
            return this.Equals(other.m_Value);
        }

        private bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object obj)
        {
            return obj is WindowsTargetPlatformVersion other && this.Equals(other);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }

        public static bool operator ==(WindowsTargetPlatformVersion left, WindowsTargetPlatformVersion right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(WindowsTargetPlatformVersion left, WindowsTargetPlatformVersion right)
        {
            return !(left == right);
        }
    }
}
