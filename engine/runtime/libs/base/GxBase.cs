using Graphyte.Build;

namespace Graphyte
{
    public class GxBase : ModuleProject
    {
        public override void Configure(Target target, IContext configuration)
        {
            base.Configure(target, configuration);

            target.PublicIncludePaths.Add("engine/runtime/libs/base/public");
            target.PublicIncludePaths.Add("engine/include");

            target.AddPublicDependency<SdkFmt>();
            target.AddPrivateDependency<SdkLz4>();

            if (configuration.Platform != PlatformType.UWP)
            {
                target.AddPrivateDependency<SdkMbedtls>();
            }


            if (configuration.Platform == PlatformType.Windows || configuration.Platform == PlatformType.UWP)
            {
                target.PublicLibraries.Add("ntdll.lib");
                target.PublicLibraries.Add("comctl32.lib");
                target.PublicLibraries.Add("iphlpapi.lib");
                target.PublicLibraries.Add("ws2_32.lib");
                target.PublicLibraries.Add("dwmapi.lib");
                target.PublicLibraries.Add("xinput.lib");
                target.PublicLibraries.Add("xaudio2.lib");
                target.PublicLibraries.Add("advapi32.lib");
                target.PublicLibraries.Add("gdi32.lib");
                target.PublicLibraries.Add("shell32.lib");
                target.PublicLibraries.Add("ole32.lib");
                target.PublicLibraries.Add("Faultrep.lib");
                target.PublicLibraries.Add("Bcrypt.lib");
                target.PublicLibraries.Add("user32.lib");
                target.PublicLibraries.Add("Mincore.lib");

                if (configuration.Build != BuildType.Retail)
                {
                    target.PrivateLibraries.Add("dbghelp.lib");
                }
            }
            else if (configuration.Platform == PlatformType.Linux)
            {
                target.PublicLibraries.Add("pthread");
                target.PublicLibraries.Add("uuid");
                target.PublicLibraries.Add("dl");
                target.PublicLibraries.Add("SDL2");
                target.PublicLibraries.Add("unwind");
                target.PublicLibraries.Add("unwind -generic");

                if (configuration.Architecture == ArchitectureType.X64)
                {
                    target.PublicLibraries.Add("unwind-x86_64");
                }
                else if (configuration.Architecture == ArchitectureType.Arm64)
                {

                    target.PublicLibraries.Add("unwind-aarch64");

                }
            }
        }
    }
}
