using Graphyte.Build;

namespace Graphyte
{
    [ProvideSourceLocation]
    public class SdkCatch2 : Project
    {
        public override void Configure(Target target)
        {
            target.TargetType = TargetType.HeaderLibrary;
            target.PublicIncludePaths.Add("sdks/catch2/include");
        }
    }
}
