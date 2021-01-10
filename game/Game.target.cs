
using Neobyte.Build.Framework;

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
}
