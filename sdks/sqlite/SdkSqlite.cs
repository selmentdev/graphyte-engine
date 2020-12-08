using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class SdkSqlite : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.StaticLibrary;
            target.PublicIncludePaths.Add("sdks/sqlite/include");
        }
    }
}
