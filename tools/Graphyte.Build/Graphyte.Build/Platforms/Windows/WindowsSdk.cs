using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Graphyte.Build.Platforms.Windows
{
    public static class WindowsSdk
    {
        private static readonly string[] CPlusPlusSdkOptions = new[]
        {
            "OptionId.DesktopCPPx64",
            "OptionId.DesktopCPParm64",
            "OptionId.SigningTools",
            "OptionId.UWPCPP",
        };

        public static IReadOnlyList<WindowsTargetPlatformVersion> Availablle { get; }
        public static string Location { get; }


        static WindowsSdk()
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                #region Detect Windows SDK
                var root = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry64);
                var roots = root.OpenSubKey(@"SOFTWARE\WOW6432Node\Microsoft\Windows Kits\Installed Roots");

                var kitsroot10name = roots.GetValueNames().Where(x => x.StartsWith(@"KitsRoot10")).First();
                WindowsSdk.Location = (string)roots.GetValue(kitsroot10name);

                var sdkNames = roots.GetSubKeyNames().Where(x => x.StartsWith("10."));
                var sdksFound = new List<WindowsTargetPlatformVersion>();

                foreach (var sdkName in sdkNames)
                {
                    var sdk = roots.OpenSubKey(sdkName);
                    var installedOptions = sdk.OpenSubKey("Installed Options");
                    var options = installedOptions.GetValueNames();

                    var all = WindowsSdk.CPlusPlusSdkOptions.All(x => options.Contains(x));

                    if (all)
                    {
                        sdksFound.Add(WindowsTargetPlatformVersion.Create(sdkName));
                    }
                    else
                    {
                        Debug.WriteLine($@"{sdkName} does not have all required options");
                    }
                }

                WindowsSdk.Availablle = sdksFound;
                #endregion
            }
        }
    }
}
