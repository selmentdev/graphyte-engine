using Graphyte.Build;

namespace Graphyte
{
    public class SdkSqlite : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.StaticLibrary;
            target.PublicIncludePaths.Add("sdks/sqlite/include");
        }
    }
}
