using System;

namespace GraphyteBuildTool
{
    public enum ArchitectureType
    {
        X64,
        ARM64,
        PPC64,
    }

    public static class ArchitectureTypeExtensions
    {
        public static bool Is64Bit(this ArchitectureType value)
        {
            switch (value)
            {
                case ArchitectureType.X64:
                case ArchitectureType.ARM64:
                case ArchitectureType.PPC64:
                    return true;
                default:
                    throw new Exception($@"Unknown architecture type {value}");
            }
        }
    }
}
