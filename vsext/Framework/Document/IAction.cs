using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Framework.Document
{
    public interface IAction
    {
        void Execute();
        void Reverse();
    }
}
