using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis;
using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.CodeAnalysis.CSharp;
using System.Linq;

namespace OmnityEngine.Build.SourceGenerator
{
    internal static class Utils
    {
        public static bool TryGetAttribute(SyntaxList<AttributeListSyntax> attLists, string[] name, out AttributeSyntax attr)
        {
            foreach (var attlist in attLists)
            {
                foreach (var att in attlist.Attributes)
                {
                    if (!name.Where(n => n == att.Name.ToString()).Any())
                        continue;
                    attr = att;
                    return true;
                }
            }
            attr = null;
            return false;
        }
    }
}
