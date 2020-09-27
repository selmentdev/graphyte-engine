using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build
{
    public abstract class Project
    {
        public abstract void Configure(ConfiguredTarget target, ConfigurationContext context);

        public string Name
        {
            get
            {
                return this.GetType().Name;
            }
        }
    }
}
