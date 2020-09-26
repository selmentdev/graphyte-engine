using System;
using System.Collections.Generic;

namespace Graphyte.Build.Engine
{
    internal static class ResolveUtils
    {
        public static IEnumerable<T> PostOrder<T>(T node, Func<T, IEnumerable<T>> selector)
        {
            // Get children of node first
            var children = selector(node);

            foreach (var child in children)
            {
                foreach (var item in PostOrder<T>(child, selector))
                {
                    yield return item;
                }
            }

            yield return node;
        }
    }
}
