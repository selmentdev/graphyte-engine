using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text.Json;

namespace Graphyte.Build.Platforms.Windows
{
    public static class ToolchainHelpers
    {
        private static readonly string[] CPlusPlusSdkOptions = new[]
        {
            "OptionId.DesktopCPPx64",
            "OptionId.DesktopCPParm64",
            "OptionId.SigningTools",
            "OptionId.UWPCPP",
        };

        public static bool IsWindows
        {
            get
            {
                return RuntimeInformation.IsOSPlatform(OSPlatform.Windows);
            }
        }

        static ToolchainHelpers()
        {
            if (ToolchainHelpers.IsWindows)
            {
                var root = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry64);
                var roots = root.OpenSubKey(@"SOFTWARE\WOW6432Node\Microsoft\Windows Kits\Installed Roots");

                var kitsroot10name = roots.GetValueNames().Where(x => x.StartsWith(@"KitsRoot10")).First();
                ToolchainHelpers.WindowsSdkLocation = (string)roots.GetValue(kitsroot10name);



                var sdkNames = roots.GetSubKeyNames().Where(x => x.StartsWith("10."));
                var sdksFound = new List<Version>();

                foreach (var sdkName in sdkNames)
                {
                    var sdk = roots.OpenSubKey(sdkName);
                    var installedOptions = sdk.OpenSubKey("Installed Options");
                    var options = installedOptions.GetValueNames();

                    var all = ToolchainHelpers.CPlusPlusSdkOptions.All(x => options.Contains(x));

                    if (all)
                    {
                        sdksFound.Add(Version.Parse(sdkName));
                    }
                    else
                    {
                        Console.WriteLine($@"{sdkName} does not have all required options");
                    }
                }

                ToolchainHelpers.Windows10Sdks = sdksFound;

                var msvcPath = Environment.GetEnvironmentVariable("ProgramFiles(x86)");

                if (msvcPath != null)
                {
                    var vswherePath = Path.Combine(
                            msvcPath,
                            "Microsoft Visual Studio",
                            "Installer",
                            "vswhere.exe");

                    var vswhere = new Process()
                    {
                        StartInfo = new ProcessStartInfo()
                        {
                            FileName = vswherePath,
                            Arguments = "-utf8 -latest -products * -format json",
                            UseShellExecute = false,
                            RedirectStandardOutput = true,
                        },
                    };

                    if (vswhere.Start())
                    {
                        var content = vswhere.StandardOutput.ReadToEnd();
                        var document = JsonDocument.Parse(content);

                        foreach (var instance in document.RootElement.EnumerateArray())
                        {
                            var properties = instance.EnumerateObject().ToDictionary(x => x.Name, x => x.Value);
                            var name = properties["displayName"];
                            var path = properties["installationPath"];
                            var version = properties["catalog"].EnumerateObject().First(x => x.Name == "productLineVersion").Value;

                            Console.WriteLine($@"Name: {name}, Path: {path}, Version: {version}");
                        }
                    }
                }
            }
        }

        public static string? WindowsSdkLocation { get; }

        public static IReadOnlyList<Version>? Windows10Sdks { get; }
    }
}
