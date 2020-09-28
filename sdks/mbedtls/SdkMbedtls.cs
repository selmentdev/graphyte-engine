using Graphyte.Build;

namespace Graphyte
{
    public class SdkMbedtls : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.StaticLib;
            target.IncludePaths.Add("sdks/mbedtls/include");

            if (configuration.Architecture == ArchitectureType.X64)
            {
                target.PrivateDefines["MBEDTLS_HAVE_SSE2"] = "1";
            }
        }
    }
}
