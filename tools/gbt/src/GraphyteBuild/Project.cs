namespace Graphyte.Build
{
    public abstract class Project
        : IConfigurable
    {
        public abstract void Configure(ConfiguredTarget target, ConfigurationContext configuration);

        public string Name
        {
            get
            {
                return this.GetType().Name;
            }
        }
    }
}
