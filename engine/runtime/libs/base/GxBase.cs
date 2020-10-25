using Graphyte.Build;

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

            if (target.TargetTuple.Platform != Platform.UWP)
            {
                target.AddPrivateDependency<SdkMbedtls>();
            }


            if (target.TargetTuple.Platform == Platform.Windows || target.TargetTuple.Platform == Platform.UWP)
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

                if (target.TargetTuple.Configuration != Configuration.Release)
                {
                    target.PrivateLibraries.Add("dbghelp.lib");
                }
            }
            else if (target.TargetTuple.Platform == Platform.Linux)
            {
                target.PublicLibraries.Add("pthread");
                target.PublicLibraries.Add("uuid");
                target.PublicLibraries.Add("dl");
                target.PublicLibraries.Add("SDL2");
                target.PublicLibraries.Add("unwind");
                target.PublicLibraries.Add("unwind -generic");

                if (target.TargetTuple.Architecture == Architecture.X64)
                {
                    target.PublicLibraries.Add("unwind-x86_64");
                }
                else if (target.TargetTuple.Architecture == Architecture.ARM64)
                {

                    target.PublicLibraries.Add("unwind-aarch64");

                }
            }
        }
    }
}
