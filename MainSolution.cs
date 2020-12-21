using Neobyte.Build.Framework;
using System;

[assembly: Neobyte.Build.Core.TypesProvider]

namespace Graphyte
{
    class Program
    {
        static int Main(string[] args)
        {
            return Neobyte.Build.Application.Main(args);
        }
    }
}

namespace Graphyte
{
    [TargetRules]
    [TargetRulesFlavor(TargetFlavor.Client)]
    [TargetRulesFlavor(TargetFlavor.Server)]
    [TargetRulesFlavor(TargetFlavor.Editor)]
    [TargetRulesFlavor(TargetFlavor.Game)]
    public class GameTarget
        : TargetRules
    {
        public GameTarget(TargetDescriptor descriptor, TargetContext context)
            : base(descriptor, context)
        {
            this.LaunchModule = typeof(DemoApp);
            this.Type = TargetType.Game;
            this.LinkType = TargetLinkType.Modular;
        }
    }

    public abstract class GraphyteModule
        : ModuleRules
    {
        protected GraphyteModule(TargetRules target)
            : base(target)
        {
            // BUG:
            //      This should be resolved only when default is set, only when applicable.
            //      All modules should have this logic, not only engine modules.
            //
            // TODO:
            //      Move this code to Target.

            this.Type = (target.LinkType == TargetLinkType.Monolithic)
                ? ModuleType.StaticLibrary
                : ModuleType.SharedLibrary;

            this.PrivateDefines.Add("GX_BUILD_TYPE_DEVELOPER=1");

            switch (target.Descriptor.Configuration)
            {
                case TargetConfiguration.Debug:
                    this.PublicDefines.Add("GX_CONFIG_DEBUG=1");
                    break;

                case TargetConfiguration.DebugGame:
                    this.PublicDefines.Add("GX_CONFIG_DEBUG_GAME=1");
                    break;

                case TargetConfiguration.Development:
                    this.PublicDefines.Add("GX_CONFIG_DEVELOPMENT=1");
                    break;

                case TargetConfiguration.Release:
                    this.PublicDefines.Add("GX_CONFIG_RELEASE=1");
                    break;

                case TargetConfiguration.Testing:
                    this.PublicDefines.Add("GX_CONFIG_TESTING=1");
                    break;

                default:
                    throw new NotSupportedException();
            }
        }
    }
}
