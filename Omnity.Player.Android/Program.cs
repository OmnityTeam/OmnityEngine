
using OmnityEngine.Core;
using OmnityEngine.Core.Graphic.LowLevel;
using OmnityEngine.Core.Native;
using System.Runtime.InteropServices;

[Activity(MainLauncher =true)]
class MainActivity : Activity
{
    protected override void OnCreate(Bundle? savedInstanceState)
    {
        base.OnCreate(savedInstanceState);
        var app = new OmnityEngine.Core.Application(new ApplicationInfo
        {
            graphicApi = GraphicApi.Vulkan
        });
        var buffer = app.GraphicContext.CreateIndexBuffer();
        Console.WriteLine($"{NativeDiagnosis.GetNativeObjectTotal()}(Shared {NativeDiagnosis.GetNativeSharedObjectTotal()})");
        buffer?.Dispose();
        buffer = null;
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Console.WriteLine($"{NativeDiagnosis.GetNativeObjectTotal()}(Shared {NativeDiagnosis.GetNativeSharedObjectTotal()})");
        new AlertDialog.Builder(this).SetTitle("HelloWorld").SetMessage("HelloWorld" + OmnityEngine.Core.Application.Platform.ToString()).Show();
    }
}