namespace GraphyteBuildTool
{
    public struct Configuration
    {
        public Configuration(PlatformType platform, ArchitectureType architecture, BuildType build, ConfigType config)
        {
            this.Platform = platform;
            this.Architecture = architecture;
            this.Build = build;
            this.Config = config;
        }
        public PlatformType Platform { get; private set; }
        public ArchitectureType Architecture { get; private set; }
        public BuildType Build { get; private set; }
        public ConfigType Config { get; private set; }

        public override string ToString()
        {
            return $@"{this.Platform}_{this.Architecture}_{this.Build}_{this.Config}";
        }
    }
}
