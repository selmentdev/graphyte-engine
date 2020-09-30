using Graphyte.Build;

namespace Graphyte
{
    public class SdkLz4 : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.StaticLibrary;
            target.PublicIncludePaths.Add("sdks/lz4/include");
        }
    }
}
