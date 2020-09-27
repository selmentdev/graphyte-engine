using System;
using Graphyte.Build;
using Graphyte.Build.Platforms.Windows;

namespace Graphyte
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine($@"Location: {WindowsSdk.Location}");

            foreach (var version in WindowsSdk.Availablle)
            {
                Console.WriteLine($@"Version: {version}");
            }

            foreach (var vs in Graphyte.Build.Toolchains.VisualStudio.VisualStudioProvider.Locations)
            {
                Console.WriteLine($@"VS ({vs.Name}, {vs.Version}, {vs.Location})");
            }
        }
    }
}
