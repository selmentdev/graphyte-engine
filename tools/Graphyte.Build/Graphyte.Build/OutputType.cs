using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public enum OutputType
    {
        /// <summary>
        /// Compiles project as static library.
        /// </summary>
        StaticLib,

        /// <summary>
        /// Compiles project as shared library.
        /// </summary>
        SharedLib,

        /// <summary>
        /// Defines project with header only library.
        /// </summary>
        HeaderLib,

        /// <summary>
        /// Library is precompiled. It must provide ExportedLibsPaths.
        /// </summary>
        ExternLib,

        /// <summary>
        /// Developer application.
        /// </summary>
        DeveloperApplication,
        /// <summary>
        /// Actual game application.
        /// </summary>
        GameApplication,

        /// <summary>
        /// Test application.
        /// </summary>
        TestApplication,
    }
}
