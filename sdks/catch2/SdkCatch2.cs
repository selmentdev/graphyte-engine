using Graphyte.Build;

namespace Graphyte
{
    public class SdkCatch2 : Project
    {
        public override void Configure(Target target, IContext configuration)
        {
            target.Type = TargetType.HeaderLibrary;
            target.PublicIncludePaths.Add("sdks/catch2/include");
        }
    }
}
