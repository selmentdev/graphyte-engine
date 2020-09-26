namespace Graphyte.Build
{
    public class TargetType
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
