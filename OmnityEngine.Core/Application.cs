using OmnityEngine.Core.Graphic;
using OmnityEngine.Core.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core
{
    public enum PlatformName
    {
        Windows = 1,
        Android = 2,
        iOS = 3,
        Unknown = 999
    }

    public partial class Application : IDisposable
    {
        [LibraryImport("OmnityNative", EntryPoint = "Application__GetEngineVersion")]
        private static partial ulong GetEngineVersion();
        public static ulong EngineVersion => GetEngineVersion();


        [LibraryImport("OmnityNative", EntryPoint = "Application__GetPlatformId")]
        private static partial ushort GetPlatformId();
        public static ushort PlatformId => GetPlatformId();
        public static PlatformName Platform => PlatformId switch
        {
            1 => PlatformName.Windows,
            2 => PlatformName.Android,
            3 => PlatformName.iOS,
            _ => PlatformName.Unknown
        };

        public GraphicHost GraphicHost { get; }
        public ApplicationInfo Info { get; }
        public Application(ApplicationInfo appInfo)
        {
            Info = appInfo;
            GraphicHost = new GraphicHost(Info.graphicApi);
        }

        public void Dispose()
        {
            GraphicHost.Dispose();
        }
    }

    public struct ApplicationInfo
    {
        public GraphicApi graphicApi;
    }
}