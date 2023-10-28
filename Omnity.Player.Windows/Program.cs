using OmnityEngine.Core;
using OmnityEngine.Core.Native;

void run()
{
    var app = Application.CreateInstance();
    var buffer = app.Graphic.CreateBuffer();
    //buffer.Dispose();
    //app.Dispose();
}
run();
GC.Collect();
GC.WaitForPendingFinalizers();
return 0;