using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace Graphyte.Build.Resolver
{
    [Serializable]
    public class ResolverException : Exception
    {
        public ResolverException()
        {
        }

        public ResolverException(string message)
            : base(message)
        {
        }

        public ResolverException(string message, Exception inner)
            : base(message, inner)
        {
        }

        protected ResolverException(
            SerializationInfo info,
            StreamingContext context)
            : base(info, context)
        {
        }
    }
}
