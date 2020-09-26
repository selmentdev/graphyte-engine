
using System.Collections.Generic;

namespace Graphyte.Build
{
    public class Solution
    {
        private List<Project> m_Projects = new List<Project>();
        private List<TargetType> m_TargetTypes = new List<TargetType>();
        private List<BuildType> m_BuildTypes = new List<BuildType>();
        private List<ConfigurationType> m_ConfigurationTypes = new List<ConfigurationType>();

        public IReadOnlyList<Project> Projects
        {
            get
            {
                return this.m_Projects;
            }
        }

        public IReadOnlyList<TargetType> TargetTypes
        {
            get
            {
                return this.m_TargetTypes;
            }
        }

        public IReadOnlyList<BuildType> BuildTypes
        {
            get
            {
                return this.m_BuildTypes;
            }
        }

        public IReadOnlyList<ConfigurationType> ConfigurationTypes
        {
            get
            {
                return this.m_ConfigurationTypes;
            }
        }

        private string? m_Name;
        public virtual string Name
        {
            get
            {
                if (this.m_Name != null)
                {
                    return this.m_Name;
                }
                return this.GetType().Name;
            }
            set
            {
                this.m_Name = value;
            }
        }

        protected void AddProject<T>() where T : Project, new()
        {
            m_Projects.Add(new T());
        }

        protected void AddBuildType(BuildType value)
        {
            this.m_BuildTypes.Add(value);
        }

        protected void AddConfigurationType(ConfigurationType value)
        {
            this.m_ConfigurationTypes.Add(value);
        }

        protected void AddTarget(TargetType target)
        {
            this.m_TargetTypes.Add(target);
        }

        /// <summary>
        /// Pre-configures project target.
        /// </summary>
        public virtual void PreConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
        }

        public virtual void PostConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
        }
    }
}
