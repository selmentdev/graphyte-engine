using System;
using System.IO;
using System.Text.Json;
using System.Xml.Serialization;

namespace Graphyte.Build.Application
{
    public sealed class BuildProfile
    {
        public bool EnableAddressSanitizer { get; set; }

        public bool EnableThreadSanitizer { get; set; }
        public bool EnableUndefinedBehaviorSanitizer { get; set; }
        public bool EnableUnityBuild { get; set; }
        public bool EnableMemorySanitizer { get; set; }
        public bool ForceUnityBuild { get; set; }
        public bool CreateMapFile { get; set; }
    }

    public static class BuildProfileSupport
    {
        private static JsonSerializerOptions m_Options = new JsonSerializerOptions()
        {
            AllowTrailingCommas = true,
            WriteIndented = true,
            ReadCommentHandling = JsonCommentHandling.Skip,
        };

        public static void Save(BuildProfile profile, string path)
        {
            var content = JsonSerializer.Serialize<BuildProfile>(profile, m_Options);
            if (content != null)
            {
                File.WriteAllText(path, content);
            }
            else
            {
                throw new Exception("Cannot serialize profile");
            }
        }

        public static BuildProfile Load(string path)
        {
            var content = File.ReadAllText(path);
            return JsonSerializer.Deserialize<BuildProfile>(content, m_Options);
        }
    }
}
