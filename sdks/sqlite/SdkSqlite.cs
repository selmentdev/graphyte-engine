using Graphyte.Build;

namespace Graphyte
{
    public class SdkSqlite : Target
    {
        public override void Configure(ConfiguredTarget target, ConfigurationContext configuration)
        {
            target.Type = OutputType.StaticLib;
            target.IncludePaths.Add("sdks/sqlite/include");
        }
    }
}
