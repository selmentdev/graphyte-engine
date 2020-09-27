using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public readonly struct TargetType
    {
        public PlatformType Platform { get; }
        public ArchitectureType Architecture { get; }

        public TargetType(
            PlatformType platform,
            ArchitectureType architecture)
        {
            this.Platform = platform;
            this.Architecture = architecture;
        }

        public override string ToString()
        {
            return $@"{this.Platform} {this.Architecture}";
        }
    }
}
