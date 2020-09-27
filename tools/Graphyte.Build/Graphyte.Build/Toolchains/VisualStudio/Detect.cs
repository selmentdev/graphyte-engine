using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.Json;

namespace Graphyte.Build.Toolchains.VisualStudio
{
    public readonly struct VisualStudioLocation
    {
        public string Location { get; }
        public string Name { get; }
        public string Version { get; }

        public VisualStudioLocation(string location, string name, string version)
        {
            this.Location = location;
            this.Name = name;
            this.Version = version;
        }
    }

    public static class VisualStudioProvider
    {
        public static IReadOnlyList<VisualStudioLocation> Locations { get; }

        static VisualStudioProvider()
        {
            var locations = new List<VisualStudioLocation>();

            if (Platforms.Windows.WindowsPlatformProvider.IsAvailable)
            {
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

                            locations.Add(new VisualStudioLocation(
                                location: path.GetString(),
                                name: name.GetString(),
                                version: version.GetString()));
                        }
                    }
                }
            }

            VisualStudioProvider.Locations = locations;
        }
    }
}
