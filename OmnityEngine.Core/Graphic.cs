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
    public enum GraphicApi
    {
        Vulkan = 0,
        Directx = 1
    }

    public partial class Graphic : NativeObject<Graphic>
    {
        [LibraryImport("OmnityNative", EntryPoint = "Graphic__Ctor")]
        private static partial NativePointer<Graphic> Ctor(GraphicApi api);
        public Graphic(GraphicApi api) : base(Ctor(api)) { }


        [LibraryImport("OmnityNative", EntryPoint = "Graphic__CreateBuffer")]
        private static partial NativePointer<Buffer> CreateBuffer(NativePointer<Graphic> _this);
        public Buffer CreateBuffer() => new(CreateBuffer(this));
    }

    public class Buffer : NativeObject<Buffer>
    {
        internal Buffer(NativePointer<Buffer> handle) : base(handle) { }
    }
}
