using OmnityEngine.Core.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Graphic
{
    internal class GpuDevice : NativeObject<GpuDevice>
    {
        internal GpuDevice(NativePointer<GpuDevice> pointer) : base(pointer) { }
    }
}
