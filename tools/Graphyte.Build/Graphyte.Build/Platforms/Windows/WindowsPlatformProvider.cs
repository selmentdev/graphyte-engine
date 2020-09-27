using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Graphyte.Build.Platforms.Windows
{
    public class WindowsPlatformProvider : IPlatformProvider
    {
        public static bool IsAvailable
        {
            get
            {
                return RuntimeInformation.IsOSPlatform(OSPlatform.Windows);
            }
        }
    }
}
