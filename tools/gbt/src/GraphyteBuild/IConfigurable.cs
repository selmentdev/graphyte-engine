namespace Graphyte.Build
{
    public interface IConfigurable
    {
        void Configure(ConfiguredTarget target, ConfigurationContext context);
    }
}
