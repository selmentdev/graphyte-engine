using System;

namespace Graphyte.Build
{
    public abstract class BasePlatform
    {
        public PlatformType Type { get; }

        public BasePlatform(PlatformType platformType)
        {
            this.Type = platformType;
        }

        public abstract string GetImageFileName(OutputType type, string name);
    }

    public class WindowsPlatform : BasePlatform
    {
        public WindowsPlatform()
            : base(PlatformType.Windows)
        {
        }

        public override string GetImageFileName(OutputType type, string name)
        {
            switch (type)
            {
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return $@"{name}.exe";

                case OutputType.StaticLib:
                    return $@"lib{name}.lib";

                case OutputType.SharedLib:
                    return $@"lib{name}.dll";

                case OutputType.HeaderLib:
                case OutputType.ExternLib:
                    return name;
            }

            throw new Exception($@"Output type {type} is not supported");
        }
    }

    public class UWPPlatform : BasePlatform
    {
        public UWPPlatform()
            : base(PlatformType.UWP)
        {
        }

        public override string GetImageFileName(OutputType type, string name)
        {
            switch (type)
            {
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return $@"{name}.exe";

                case OutputType.StaticLib:
                    return $@"lib{name}.lib";

                case OutputType.SharedLib:
                    return $@"lib{name}.dll";

                case OutputType.HeaderLib:
                case OutputType.ExternLib:
                    return name;
            }

            throw new Exception($@"Output type {type} is not supported");
        }
    }

    public class LinuxPlatform : BasePlatform
    {
        public LinuxPlatform()
            : base(PlatformType.Windows)
        {
        }

        public override string GetImageFileName(OutputType type, string name)
        {
            switch (type)
            {
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return $@"{name}.elf";

                case OutputType.StaticLib:
                    return $@"lib{name}.a";

                case OutputType.SharedLib:
                    return $@"lib{name}.so";

                case OutputType.HeaderLib:
                case OutputType.ExternLib:
                    return name;
            }

            throw new Exception($@"Output type {type} is not supported");
        }
    }
}
