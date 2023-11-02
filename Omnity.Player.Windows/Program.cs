using OmnityEngine.Core;
using OmnityEngine.Core.Graphic;
using OmnityEngine.Core.Native;

void run()
{
    using var app = new Application(new ApplicationInfo
    {
        graphicApi = GraphicApi.Vulkan
    });
    //buffer.Dispose();
    //app.Dispose();
}
run();
//GC.Collect();
//GC.WaitForPendingFinalizers();
return 0;