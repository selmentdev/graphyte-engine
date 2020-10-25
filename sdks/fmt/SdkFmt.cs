using Graphyte.Build;

namespace Graphyte
{
    public class SdkFmt : Project
    {
        public override void Configure(Target target)
        {
            if (target.TargetTuple.Configuration == Configuration.Release)
            {
                target.TargetType = TargetType.StaticLibrary;
            }
            else
            {
                target.TargetType = TargetType.SharedLibrary;
            }

            target.PublicIncludePaths.Add("sdks/fmt/include");
            target.PublicDefines.Add("FMT_EXCEPTIONS=1");
            target.PublicDefines.Add("FMT_EXPORT=1");
            target.PublicDefines.Add("_CRT_SECURE_NO_WARNINGS=0");
        }
    }
}
