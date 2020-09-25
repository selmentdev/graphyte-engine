using System.Collections.Generic;

namespace GraphyteBuildTool.Platforms
{
    public static class PlatformProvider
    {
        public static IReadOnlyDictionary<PlatformType, BasePlatform> Platforms { get; } = new Dictionary<PlatformType, BasePlatform>()
        {
            [PlatformType.Windows] = new WindowsPlatform(),
            [PlatformType.UWP] = new UWPPlatform(),
            [PlatformType.Linux] = new LinuxPlatform(),
        };
    }
}
