using OmnityEngine.Core.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Graphic
{
    public enum GraphicApi
    {
        Vulkan = 0,
        Directx = 1
    }

    public partial class GraphicHost : NativeObject<GraphicHost>
    {
        [LibraryImport("OmnityNative", EntryPoint = "GraphicHost__Ctor")]
        private static partial NativePointer<GraphicHost> Ctor(GraphicApi api);
        public GraphicHost(GraphicApi api) : base(Ctor(api)) { }
    }
}
