using System;
using System.Diagnostics.CodeAnalysis;

namespace Graphyte.Build.Platforms.Windows
{
    public readonly struct WindowsTargetPlatformVersion : IEquatable<WindowsTargetPlatformVersion>
    {
        public static WindowsTargetPlatformVersion V10_0_18362_0 = new WindowsTargetPlatformVersion("10.0.18362.0");
        public static WindowsTargetPlatformVersion V10_0_19041_0 = new WindowsTargetPlatformVersion("10.0.19041.0");

        private readonly string m_Value;

        public static WindowsTargetPlatformVersion Create(string value)
        {
            return new WindowsTargetPlatformVersion(value);
        }

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

        public override string ToString() => this.m_Value ?? string.Empty;

        public bool Equals([AllowNull]WindowsTargetPlatformVersion other)
        {
            return Equals(other.m_Value);
        }

        internal bool Equals(string value)
        {
            return string.Equals(this.m_Value, value, StringComparison.Ordinal);
        }

        public override bool Equals(object? obj)
        {
            return obj is WindowsTargetPlatformVersion other && this.Equals(other);
        }

        public static bool operator==(WindowsTargetPlatformVersion left, WindowsTargetPlatformVersion right)
        {
            return left.Equals(right);
        }

        public static bool operator!=(WindowsTargetPlatformVersion left, WindowsTargetPlatformVersion right)
        {
            return !(left == right);
        }

        public override int GetHashCode()
        {
            return this.m_Value.GetHashCode();
        }
    }
}
