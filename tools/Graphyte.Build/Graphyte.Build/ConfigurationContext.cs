using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public sealed class ConfigurationContext
    {
        public PlatformType Platform { get; }
        public ArchitectureType Architecture { get; }
        public ConfigurationType Configuration { get; }
        public BuildType Build { get; }

        public ConfigurationContext(
            PlatformType platform,
            ArchitectureType architecture,
            BuildType build,
            ConfigurationType configuration)
        {
            this.Platform = platform;
            this.Architecture = architecture;
            this.Build = build;
            this.Configuration = configuration;
        }

        public ConfigurationContext(
            TargetType target,
            BuildType build,
            ConfigurationType configuration)
            : this(target.Platform, target.Architecture, build, configuration)
        {
        }

        public override string ToString()
        {
            return $@"{this.Platform} {this.Architecture} {this.Build} {this.Configuration}";
        }
    }
}
