using Graphyte.Build;

namespace Graphyte
{
    public class GxBase : ModuleProject
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            base.Configure(target, configuration);

            target.IncludePaths.Add("engine/runtime/libs/base/public");
            target.IncludePaths.Add("engine/include");

            target.AddPublicDependency<SdkFmt>();
            target.AddPrivateDependency<SdkLz4>();

            if (configuration.Platform != PlatformType.UWP)
            {
                target.AddPrivateDependency<SdkMbedtls>();
            }


            if (configuration.Platform == PlatformType.Windows || configuration.Platform == PlatformType.UWP)
            {
                target.Libraries.Add("ntdll.lib");
                target.Libraries.Add("comctl32.lib");
                target.Libraries.Add("iphlpapi.lib");
                target.Libraries.Add("ws2_32.lib");
                target.Libraries.Add("dwmapi.lib");
                target.Libraries.Add("xinput.lib");
                target.Libraries.Add("xaudio2.lib");
                target.Libraries.Add("advapi32.lib");
                target.Libraries.Add("gdi32.lib");
                target.Libraries.Add("shell32.lib");
                target.Libraries.Add("ole32.lib");
                target.Libraries.Add("Faultrep.lib");
                target.Libraries.Add("Bcrypt.lib");
                target.Libraries.Add("user32.lib");
                target.Libraries.Add("Mincore.lib");

                if (configuration.Build != BuildType.Retail)
                {
                    target.Libraries.Add("dbghelp.lib");
                }
            }
            else if (configuration.Platform == PlatformType.Linux)
            {
                target.Libraries.Add("pthread");
                target.Libraries.Add("uuid");
                target.Libraries.Add("dl");
                target.Libraries.Add("SDL2");
                target.Libraries.Add("unwind");
                target.Libraries.Add("unwind -generic");

                if (configuration.Architecture == ArchitectureType.X64)
                {
                    target.Libraries.Add("unwind-x86_64");
                }
                else if (configuration.Architecture == ArchitectureType.Arm64)
                {

                    target.Libraries.Add("unwind-aarch64");

                }
            }
        }
    }
}
