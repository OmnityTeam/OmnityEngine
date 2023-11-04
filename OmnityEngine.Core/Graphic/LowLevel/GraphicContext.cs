using OmnityEngine.Core.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Graphic.LowLevel
{
    public enum GraphicApi
    {
        Vulkan = 0,
        Directx = 1
    }

    public partial class GraphicContext : NativeObject<GraphicContext>
    {
        [LibraryImport("OmnityNative", EntryPoint = "GraphicContext__Ctor")]
        private static partial NativePointer<GraphicContext> Ctor(GraphicApi api);
        internal GraphicContext(GraphicApi api) : base(Ctor(api)) { }

        [LibraryImport("OmnityNative", EntryPoint = "GraphicContext__CreateIndexBuffer")]
        private static partial NativePointer<IndexBuffer> CreateIndexBuffer(NativePointer<GraphicContext> _this);
        public IndexBuffer CreateIndexBuffer() => new(CreateIndexBuffer(this));
    }
}
