using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public class Solution
    {
        #region Fields
        private readonly List<Project> m_Projects = new List<Project>();
        private readonly List<TargetType> m_TargetTypes = new List<TargetType>();
        private readonly List<BuildType> m_BuildTypes = new List<BuildType>();
        private readonly List<ConfigurationType> m_ConfigurationTypes = new List<ConfigurationType>();
        #endregion

        #region Properties
        public IReadOnlyList<Project> Projects => m_Projects;
        public IReadOnlyList<TargetType> TargetTypes => m_TargetTypes;
        public IReadOnlyList<BuildType> BuildTypes => m_BuildTypes;
        public IReadOnlyList<ConfigurationType> ConfigurationTypes => m_ConfigurationTypes;
        #endregion

        #region Solution Name
        private string m_Name = null;
        public string Name
        {
            get
            {
                if (this.m_Name == null)
                {
                    return this.GetType().Name;
                }

                return this.m_Name;
            }
            set
            {
                this.m_Name = value;
            }
        }
        #endregion

        #region Solution Setup
        protected void AddProject(Project project)
        {
            this.m_Projects.Add(project);
        }

        protected void AddTarget(PlatformType platform, ArchitectureType architecture)
        {
            this.m_TargetTypes.Add(new TargetType(platform, architecture));
        }

        protected void AddBuild(BuildType value)
        {
            this.m_BuildTypes.Add(value);
        }

        protected void AddConfiguration(ConfigurationType configuration)
        {
            this.m_ConfigurationTypes.Add(configuration);
        }
        #endregion

        #region Resolving
        protected internal virtual void PreConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
        }

        protected internal virtual void PostConfigure(ConfiguredTarget target, ConfigurationContext context)
        {
        }
        #endregion
    }
}
