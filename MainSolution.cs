using Neobyte.Build.Core;
using Neobyte.Build.Framework;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;

[assembly: Neobyte.Build.Core.TypesProvider]

namespace Graphyte
{
    class Program
    {
        static int Main(string[] args)
        {
            using (var writer = File.CreateText(Path.Combine("engine", "include", "Graphyte", "Build.Version.hxx")))
            {
                ConfigurationFile.Write(writer, new(1, 2, 3, 4));
            }

            return Neobyte.Build.Application.Main(args);
        }
    }
}

namespace Graphyte
{
    public static class ConfigurationFile
    {
        public static void Write(StreamWriter writer, Version version)
        {
            var uniqueId = ArrayExtensions.ToString(SHA256.HashData(Encoding.UTF8.GetBytes("Graphyte")));

            writer.WriteLine($@"#define GX_BUILD_OS_VERSION         ""{Environment.OSVersion.Version}""");
            writer.WriteLine($@"#define GX_BUILD_OS_RELEASE         ""{Environment.OSVersion.Version.Major}""");
            writer.WriteLine($@"#define GX_BUILD_OS_SYSTEM          ""{Environment.OSVersion.VersionString}""");
            writer.WriteLine($@"#define GX_BUILD_MACHINE            ""{Environment.MachineName}""");
            writer.WriteLine($@"#define GX_BUILD_MACHINE_RUNTIME    ""{RuntimeInformation.RuntimeIdentifier}""");
            writer.WriteLine($@"#define GX_BUILD_COMMIT             ""{Neobyte.Base.SourceControl.Git.GetCommitId()}""");
            writer.WriteLine($@"#define GX_BUILD_COMMIT_SHORT       ""{Neobyte.Base.SourceControl.Git.GetCommitIdShort()}""");
            writer.WriteLine($@"#define GX_BUILD_BRANCH             ""{Neobyte.Base.SourceControl.Git.GetBranchName()}""");
            writer.WriteLine($@"#define GX_BUILD_UUID               ""{uniqueId}""");
            writer.WriteLine($@"#define GX_BUILD_VERSION            ""{version}""");
            writer.WriteLine($@"#define GX_BUILD_VERSION_MAJOR      {version.Major}");
            writer.WriteLine($@"#define GX_BUILD_VERSION_MINOR      {version.Minor}");
            writer.WriteLine($@"#define GX_BUILD_VERSION_RELEASE    {version.Build}");
            writer.WriteLine($@"#define GX_BUILD_VERSION_BUILD      {version.Revision}");
            writer.WriteLine($@"#define GX_BUILD_TIMESTAMP          ""{DateTime.Now:s}""");
        }
    }

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
