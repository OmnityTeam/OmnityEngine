
using OmnityEngine.Core;
using System.Runtime.InteropServices;

[Activity(MainLauncher =true)]
class MainActivity : Activity
{
    protected override void OnCreate(Bundle? savedInstanceState)
    {
        base.OnCreate(savedInstanceState);
        var app = new OmnityEngine.Core.Application();
        new AlertDialog.Builder(this).SetTitle("HelloWorld").SetMessage("HelloWorld" + app.Platform).Show();
    }
}