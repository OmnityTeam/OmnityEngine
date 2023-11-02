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

        [LibraryImport("OmnityNative", EntryPoint = "Graphic__Init")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static partial bool Init(NativeHandle<Graphic> handle, GraphicApi api);

        [LibraryImport("OmnityNative", EntryPoint = "Graphic__CreateBuffer")]
        private static partial NativeHandle<Buffer> CreateBuffer(NativeHandle<Graphic> handle);

        internal Graphic(NativeHandle<Graphic> handle) : base(handle) { }

        public Buffer CreateBuffer()
        {
            return new Buffer(CreateBuffer(Handle));
        }
    }

    public class Buffer : NativeObject<Buffer>
    {
        internal Buffer(NativeHandle<Buffer> handle) : base(handle) { }
    }
}
