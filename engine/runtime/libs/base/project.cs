using GraphyteBuildTool;
using GraphyteBuildTool.Projects;

namespace Graphyte
{
    public class GxBase : Project
    {
        public override ProjectDefinition? GetDefinition(Configuration configuration)
        {
            var result = new ProjectDefinition(this);

            if (configuration.Build == BuildType.Retail)
            {
                result.Kind = ProjectKind.StaticLib;
            }
            else
            {
                result.Kind = ProjectKind.SharedLib;
            }

            result.Dependencies.Add(nameof(SdkFmt));
            result.Dependencies.Add(nameof(SdkLz4));

            result.PublicIncludes.Add("engine/runtime/libs/base/public");

            // This project is included by default on every setup
            if (configuration.Platform == PlatformType.Windows)
            {
                result.Libraries.AddRange(new[]{
                    "ntdll.lib",
                    "comctl32.lib",
                    "dbghelp.lib",
                    "iphlpapi.lib",
                    "ws2_32.lib",
                    "dwmapi.lib",
                    "xinput.lib",
                    "xaudio2.lib",
                    "advapi32.lib",
                    "gdi32.lib",
                    "shell32.lib",
                    "ole32.lib",
                    "Faultrep.lib",
                    "Bcrypt.lib",
                    "user32.lib",
                    "Mincore.lib",
                });
                result.Dependencies.Add(nameof(SdkMbedtls));
            }
            else if (configuration.Platform == PlatformType.UWP)
            {
                result.Libraries.AddRange(new[]{
                    "ntdll.lib",
                    "comctl32.lib",
                    "dbghelp.lib",
                    "iphlpapi.lib",
                    "ws2_32.lib",
                    "dwmapi.lib",
                    "xinput.lib",
                    "xaudio2.lib",
                    "advapi32.lib",
                    "gdi32.lib",
                    "shell32.lib",
                    "ole32.lib",
                    "Faultrep.lib",
                    "Bcrypt.lib",
                    "user32.lib",
                    "Mincore.lib",
                });
            }
            else if (configuration.Platform == PlatformType.Linux)
            {
                result.Libraries.AddRange(new[]{
                    "pthread",
                    "uuid",
                    "dl",
                    "SDL2",
                    "unwind",
                    "unwind-generic",
                });
                result.Dependencies.Add(nameof(SdkMbedtls));

                if (configuration.Architecture == ArchitectureType.X64)
                {
                    result.Libraries.Add("unwind-x86_64");
                }
                else if (configuration.Architecture == ArchitectureType.ARM64)
                {
                    result.Libraries.Add("unwind-aarch64");
                }
            }

            return result;
        }
    }
}
