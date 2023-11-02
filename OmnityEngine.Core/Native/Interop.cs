using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Native
{
    internal static partial class NativeHandleCalls
    {
        [LibraryImport("OmnityNative", EntryPoint = "ObjectRefState__DangerousRelease")]
        internal static partial void Delete(IntPtr ptr);

        [LibraryImport("OmnityNative", EntryPoint = "ObjectRefState__GetRefCount")]
        internal static partial uint GetNativeRefCount(IntPtr ptr);
    }

    public partial class NativeHandle<T> : SafeHandle where T : NativeObject<T>
    {
        public static NativeHandle<T> Invalid = new NativeHandle<T>();
        public override bool IsInvalid => handle == 0;

        public NativeHandle() : base(0, true) { }

        protected override bool ReleaseHandle()
        {
            NativeHandleCalls.Delete(handle);
            handle = 0;
            return true;
        }
    }

    public abstract partial class NativeObject<T> : IDisposable where T : NativeObject<T>
    {
        internal NativeHandle<T> Handle { get; } = NativeHandle<T>.Invalid;

        protected NativeObject(NativeHandle<T> handle)
        {
            Handle = handle;
        }

        public virtual void Dispose()
        {
            Handle.Dispose();
        }
    }
}
