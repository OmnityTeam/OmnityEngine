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
    enum GraphicApi
    {
        Vulkan = 0,
        Directx = 1
    }

    public partial class Graphic : NativeObject<Graphic>
    {
        [LibraryImport("OmnityNative", EntryPoint = "Graphic__Ctor")]
        internal static partial NativeHandle<Graphic> Ctor();

        [LibraryImport("OmnityNative", EntryPoint = "Graphic__Init")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static partial bool Init(NativeHandle<Graphic> handle, GraphicApi api);

        [LibraryImport("OmnityNative", EntryPoint = "Graphic__CreateBuffer")]
        private static partial NativeHandle<Buffer> CreateBuffer(NativeHandle<Graphic> handle);

        public Buffer CreateBuffer()
        {
            return Buffer.CreateInstanceFrom(CreateBuffer(Handle));
        }
    }

    public class Buffer : NativeObject<Buffer>
    {
    }
}
