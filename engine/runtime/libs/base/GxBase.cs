using Graphyte.Build;
using Graphyte.Build.Platforms;
using Graphyte.Build.Toolchains;

namespace Graphyte
{
    public class GxBase : ModuleProject
    {
        public override void Configure(Target target)
        {
            base.Configure(target);

            target.PublicIncludePaths.Add("engine/runtime/libs/base/public");
            target.PublicIncludePaths.Add("engine/include");

            target.AddPublicDependency<SdkFmt>();
            target.AddPrivateDependency<SdkLz4>();

            if (target.PlatformType != PlatformType.UniversalWindows)
            {
                target.AddPrivateDependency<SdkMbedtls>();
            }


            if (target.PlatformType == PlatformType.Windows || target.PlatformType == PlatformType.UniversalWindows)
            {
                target.PrivateLibraries.Add("ntdll.lib");
                target.PrivateLibraries.Add("comctl32.lib");
                target.PrivateLibraries.Add("iphlpapi.lib");
                target.PrivateLibraries.Add("ws2_32.lib");
                target.PrivateLibraries.Add("dwmapi.lib");
                target.PrivateLibraries.Add("xinput.lib");
                target.PrivateLibraries.Add("xaudio2.lib");
                target.PrivateLibraries.Add("advapi32.lib");
                target.PrivateLibraries.Add("gdi32.lib");
                target.PrivateLibraries.Add("shell32.lib");
                target.PrivateLibraries.Add("ole32.lib");
                target.PrivateLibraries.Add("Faultrep.lib");
                target.PrivateLibraries.Add("Bcrypt.lib");
                target.PrivateLibraries.Add("user32.lib");
                target.PrivateLibraries.Add("Mincore.lib");

                if (target.ConfigurationType != ConfigurationType.Release)
                {
                    target.PrivateLibraries.Add("dbghelp.lib");
                }
            }
            else if (target.PlatformType == PlatformType.Linux)
            {
                target.PublicLibraries.Add("pthread");
                target.PublicLibraries.Add("uuid");
                target.PublicLibraries.Add("dl");
                target.PublicLibraries.Add("SDL2");
                target.PublicLibraries.Add("unwind");
                target.PublicLibraries.Add("unwind -generic");

                if (target.ArchitectureType == ArchitectureType.X64)
                {
                    target.PublicLibraries.Add("unwind-x86_64");
                }
                else if (target.ArchitectureType == ArchitectureType.ARM64)
                {

                    target.PublicLibraries.Add("unwind-aarch64");

                }
            }
        }
    }
}
