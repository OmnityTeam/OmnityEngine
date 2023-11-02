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

    public partial class Application : NativeObject<Application>
    {
        [LibraryImport("OmnityNative", EntryPoint = "Application__Ctor")]
        private static partial NativePointer<Application> Ctor();
        public Application() : base(Ctor())
        {
            Graphic = new(GraphicApi.Vulkan);
        }


        [LibraryImport("OmnityNative", EntryPoint = "Application__GetEngineVersion")]
        private static partial ulong GetEngineVersion(NativePointer<Application> _this);
        public ulong EngineVersion => GetEngineVersion(this);


        [LibraryImport("OmnityNative", EntryPoint = "Application__GetPlatformId")]
        private static partial ushort GetPlatformId(NativePointer<Application> _this);
        public ushort PlatformId => GetPlatformId(this);


        public Graphic Graphic { get; }

        public override void Dispose()
        {
            Graphic.Dispose();
            base.Dispose();
        }

        public PlatformName Platform => PlatformId switch
        {
            1 => PlatformName.Windows,
            2 => PlatformName.Android,
            3 => PlatformName.iOS,
            _ => PlatformName.Unknown
        };
    }
}