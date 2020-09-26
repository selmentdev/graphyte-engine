using System;

namespace Graphyte.Build
{
    public static class ArchitectureTypeExtensions
    {
        public static bool Is64Bit(this ArchitectureType value)
        {
            switch (value)
            {
                case ArchitectureType.X64:
                case ArchitectureType.ARMv8:
                case ArchitectureType.PPC64:
                    return true;
                case ArchitectureType.X86:
                case ArchitectureType.ARMv7:
                    return false;
            }

            throw new Exception($@"Unknown ArchitectureType {value}");
        }
    }
}
