using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public enum ArchitectureType
    {
        X86,
        X64,
        Arm,
        Arm64,
        PPC64,
    }
}

namespace Graphyte.Build
{
    public static class ArchitectureExtensions
    {
        public static bool Is64Bit(this ArchitectureType architecture)
        {
            switch (architecture)
            {
                case ArchitectureType.X86:
                case ArchitectureType.Arm:
                    return false;
                case ArchitectureType.X64:
                case ArchitectureType.Arm64:
                case ArchitectureType.PPC64:
                    return true;
            }

            throw new ArgumentOutOfRangeException(nameof(architecture));
        }
    }
}
