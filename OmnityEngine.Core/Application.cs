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
        internal static partial NativeHandle<Application> Ctor();

        [LibraryImport("OmnityNative", EntryPoint = "Application__Init")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static partial bool Init(NativeHandle<Application> handle);

        [LibraryImport("OmnityNative", EntryPoint = "Application__GetEngineVersion")]
        private static partial ulong GetEngineVersion(NativeHandle<Application> handle);

        [LibraryImport("OmnityNative", EntryPoint = "Application__GetPlatformId")]
        private static partial ushort GetPlatformId(NativeHandle<Application> handle);

        public Application() : base(Ctor())
        {
            Graphic = new();
        }

        public override void Dispose()
        {
            Graphic.Dispose();
            base.Dispose();
        }

        public Graphic Graphic { get; }

        public PlatformName Platform => GetPlatformId(Handle) switch
        {
            1 => PlatformName.Windows,
            2 => PlatformName.Android,
            3 => PlatformName.iOS,
            _ => PlatformName.Unknown
        };
    }
}