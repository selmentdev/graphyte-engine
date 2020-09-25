using System;
using System.Diagnostics.CodeAnalysis;

namespace GraphyteBuildTool.Projects
{
    public abstract class Project
    {
        public string Name
        {
            get
            {
                return this.GetType().Name;
            }
        }
        public abstract ProjectDefinition? GetDefinition(Configuration configuration);
    }
}
