using OmnityEngine.Core;
using OmnityEngine.Core.Graphic;
using OmnityEngine.Core.Graphic.LowLevel;
using OmnityEngine.Core.Native;

IndexBuffer? testBuffer;
Application testApp = new Application(new ApplicationInfo
{
    graphicApi = GraphicApi.Vulkan
});

while (true)
{
    testBuffer = testApp.GraphicContext.CreateIndexBuffer();
    Console.WriteLine($"{NativeDiagnosis.GetNativeObjectTotal()}(Shared {NativeDiagnosis.GetNativeSharedObjectTotal()})");
    testBuffer?.Dispose();
    testBuffer = null;
    GC.Collect();
    GC.WaitForPendingFinalizers();
    Console.WriteLine($"{NativeDiagnosis.GetNativeObjectTotal()}(Shared {NativeDiagnosis.GetNativeSharedObjectTotal()})");
}
return 0;