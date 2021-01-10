
using Neobyte.Build.Framework;

namespace Graphyte
{
    [TargetRules]
    [TargetRulesFlavor(TargetFlavor.Client)]
    [TargetRulesFlavor(TargetFlavor.Server)]
    [TargetRulesFlavor(TargetFlavor.Editor)]
    [TargetRulesFlavor(TargetFlavor.Game)]
    public class EngineTarget
    : TargetRules
    {
        public EngineTarget(TargetDescriptor descriptor, TargetContext context)
            : base(descriptor, context)
        {
            this.Type = TargetType.Editor;
            this.LinkType = TargetLinkType.Modular;
        }
    }
}
