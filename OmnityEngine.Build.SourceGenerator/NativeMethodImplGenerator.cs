using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace OmnityEngine.Build.SourceGenerator
{
    [Generator]
    public class NativeMethodImplGenerator : ISourceGenerator
    {
        public void Execute(GeneratorExecutionContext context)
        {
            var syntaxReceiver = (NativeMethodImplReceiver)context.SyntaxReceiver;
            var nativeAttr = syntaxReceiver.nativeAttributeSynatx;
            var nativeMethod = syntaxReceiver.nativeMethodSynatx;
            var declarationClass = syntaxReceiver.declarationClassSynatx;
            if (nativeAttr == null || nativeMethod == null || declarationClass == null) return;
            var nativeMethodFullname = $"{declarationClass.Identifier.ValueText}__{nativeMethod.Identifier.ValueText}";
        }
        public void Initialize(GeneratorInitializationContext context)
        {
            //Debugger.Launch();
            context.RegisterForSyntaxNotifications(() => new NativeMethodImplReceiver());
        }
    }

    class NativeMethodImplReceiver : ISyntaxReceiver
    {
        private static string[] AllowedAttributes = new[]
        {
            "OmnityNative",
            "OmnityNativeAttribute"
        };

        public MethodDeclarationSyntax nativeMethodSynatx;
        public AttributeSyntax nativeAttributeSynatx;
        public ClassDeclarationSyntax declarationClassSynatx;

        public void OnVisitSyntaxNode(SyntaxNode syntaxNode)
        {
            if (syntaxNode is MethodDeclarationSyntax mds &&
                mds.AttributeLists.Any() &&
                Utils.TryGetAttribute(mds.AttributeLists, AllowedAttributes, out var attr) &&
                mds.Parent is ClassDeclarationSyntax cds)
            {
                nativeAttributeSynatx = attr;
                nativeMethodSynatx = mds;
                declarationClassSynatx = cds;
            }
        }
    }
}
