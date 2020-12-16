using Graphyte.Build.Framework;
using System.IO;

namespace Graphyte
{
    [ModuleRules]
    public class GxBase
        : ModuleRules
    {
        public GxBase(TargetRules target)
            : base(target)
        {
            this.Type = ModuleType.SharedLibrary;
            this.Kind = ModuleKind.Runtime;
            this.Language = ModuleLanguage.CPlusPlus;

            this.PrivateDefines.AddRange(new[] {
                "__AVX__=1",
                "_WINDLL",
                "_WIN32",
                "_WIN32_WINNT=0x0A00",
                "WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP",
                "__WINDOWS__",
                "__STDC_WANT_LIB_EXT1__=1",
                "__STDINT_MACROS",
                "__STDINT_LIMITS",
                "__STDC_CONSTANT_MACROS",
                "__STDC_FORMAT_MACROS",
                "__STDC_LIMIT_MACROS",
                "_UNICODE",
                "UNICODE",
                "_HAS_EXCEPTIONS=0",
                "_HAS_ITERATOR_DEBUGGING=0",
                "_SCL_SECURE=0",
                "_SECURE_SCL=0",
                "_CRT_SECURE_INVALID_PARAMETER=",
            });

            // BUG: redefine this conditionally
            this.PrivateDefines.Add("module_base_EXPORTS=1");

            this.PublicIncludePaths.Add(Path.Combine(this.SourceDirectory.FullName, "public"));
            this.PublicIncludePaths.Add("engine/include");

            this.PrivateDependencies.Add(typeof(SdkLz4));
            this.PublicDependencies.Add(typeof(SdkFmt));

            if (target.Descriptor.Platform != TargetPlatform.UniversalWindows)
            {
                this.PrivateDependencies.Add(typeof(SdkMbedtls));
            }

            if (target.Descriptor.Platform == TargetPlatform.Windows
                || target.Descriptor.Platform == TargetPlatform.UniversalWindows)
            {
                this.PrivateLibraries.AddRange(new[] {
                    "ntdll.lib",
                    "comctl32.lib",
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
                    "msvcprtd.lib",
                });

                if (target.Descriptor.Configuration != TargetConfiguration.Release)
                {
                    this.PrivateLibraries.Add("dbghelp.lib");
                }
            }
            else if (target.Descriptor.Platform == TargetPlatform.Linux)
            {
                this.PublicLibraries.AddRange(new[] {
                    "pthread",
                    "uuid",
                    "dl",
                    "SDL2",
                    "unwind",
                    "unwind-generic",
                });

                if (target.Descriptor.Architecture == TargetArchitecture.X64)
                {
                    this.PublicLibraries.Add("unwind-x86_64");
                }
                else if (target.Descriptor.Architecture == TargetArchitecture.Arm64)
                {

                    this.PublicLibraries.Add("unwind-aarch64");

                }
            }
        }
    }
}
