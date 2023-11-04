using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.ConstrainedExecution;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace OmnityEngine.Core.Native
{
    public static partial class NativeDiagnosis
    {

        [LibraryImport("OmnityNative", EntryPoint = "CObjectRef__GetTotal")]
        public static partial ulong GetNativeObjectTotal();
        [LibraryImport("OmnityNative", EntryPoint = "CObjectRef__GetSharedTotal")]
        public static partial ulong GetNativeSharedObjectTotal();
    }

    [CustomMarshaller(typeof(NativePointer<>), MarshalMode.Default, typeof(NativeSharedPointerMarshaller<>))]
    internal static class NativeSharedPointerMarshaller<T> where T : NativeObject<T>
    {
        public static IntPtr ConvertToUnmanaged(NativePointer<T> managed)
            => managed.Pointer;

        public static NativePointer<T> ConvertToManaged(IntPtr unmanaged)
            => new(unmanaged);
    }

    internal partial class NativePointer : CriticalFinalizerObject, IDisposable
    {
        [LibraryImport("OmnityNative", EntryPoint = "CObjectRef__DangerousRelease")]
        internal static partial void Release(IntPtr ptr);

        [LibraryImport("OmnityNative", EntryPoint = "CObjectRef__GetRefCount")]
        internal static partial uint GetNativeRefCount(IntPtr ptr);

        internal IntPtr Pointer { get; private set; }

        internal NativePointer(IntPtr pointer)
        {
            Pointer = pointer;
        }

        public void Dispose()
        {
            if (Pointer != IntPtr.Zero) Release();
            GC.SuppressFinalize(this);
        }

        ~NativePointer()
        {
            Release();
        }

        private void Release()
        {
            Release(Pointer);
            Pointer = IntPtr.Zero;
        }
    }

    [NativeMarshalling(typeof(NativeSharedPointerMarshaller<>))]
    internal partial class NativePointer<T> : NativePointer where T : NativeObject<T>
    {
        internal NativePointer(IntPtr pointer) : base(pointer) { }

        public static implicit operator NativePointer<T>(NativeObject<T> obj)
        {
            return obj.SharedPtr;
        }
    }

    public abstract class NativeObject<T> where T : NativeObject<T>
    {
        internal NativePointer<T> SharedPtr { get; }
        internal NativeObject(NativePointer<T> sharedPtr)
        {
            SharedPtr = sharedPtr;
        }
        public virtual void Dispose()
        {
            SharedPtr.Dispose();
            GC.SuppressFinalize(this);
        }
    }
}
