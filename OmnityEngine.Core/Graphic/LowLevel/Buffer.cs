using OmnityEngine.Core.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Graphic.LowLevel
{
    public interface IBuffer
    {
        int Size { get; }
    }

    public partial class IndexBuffer : NativeObject<IndexBuffer>, IBuffer
    {
        [LibraryImport("OmnityNative", EntryPoint = "IndexBuffer__GetSize")]
        internal static partial int GetSize(NativePointer<IndexBuffer> _this);
        public int Size => GetSize(this);

        internal IndexBuffer(NativePointer<IndexBuffer> pointer) : base(pointer) { }
    }
}
