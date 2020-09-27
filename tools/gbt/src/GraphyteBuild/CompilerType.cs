using System;

namespace Graphyte.Build
{
    [Flags]
    public enum CompilerPersonality
    {
        None = 0,

        /// <summary>
        /// Microsoft Visual C++ compiler.
        /// </summary>
        MSVC = 1 << 0,

        /// <summary>
        /// Clang compatible compiler.
        /// </summary>
        Clang = 1 << 1,

        GCC = 1 << 2,

        ClangCL = MSVC | Clang,
    }
}
