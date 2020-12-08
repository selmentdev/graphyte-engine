using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class SdkMbedtls : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.StaticLibrary;
            target.PublicIncludePaths.Add("sdks/mbedtls/include");

            target.UseUnityFiles = false;

            if (target.ArchitectureType == ArchitectureType.X64)
            {
                target.PrivateDefines.Add("MBEDTLS_HAVE_SSE2=1");
            }
        }
    }
}
