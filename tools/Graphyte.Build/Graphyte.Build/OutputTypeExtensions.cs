using System;

namespace Graphyte.Build
{
    public static class OutputTypeExtensions
    {
        public static bool IsApplication(this OutputType value)
        {
            switch (value)
            {
                case OutputType.StaticLib:
                case OutputType.SharedLib:
                case OutputType.HeaderLib:
                case OutputType.ExternLib:
                    return false;
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return true;
            }

            throw new ArgumentOutOfRangeException(nameof(value));
        }

        public static bool IsLibrary(this OutputType value)
        {
            switch (value)
            {
                case OutputType.StaticLib:
                case OutputType.SharedLib:
                case OutputType.HeaderLib:
                case OutputType.ExternLib:
                    return true;
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return false;
            }

            throw new ArgumentOutOfRangeException(nameof(value));
        }

        public static bool IsInheritableDependency(this OutputType value)
        {
            switch (value)
            {
                case OutputType.StaticLib:
                case OutputType.HeaderLib:
                    return true;
                case OutputType.SharedLib:
                case OutputType.ExternLib:
                case OutputType.DeveloperApplication:
                case OutputType.GameApplication:
                case OutputType.TestApplication:
                    return false;
            }

            throw new ArgumentOutOfRangeException(nameof(value));
        }
    }
}
