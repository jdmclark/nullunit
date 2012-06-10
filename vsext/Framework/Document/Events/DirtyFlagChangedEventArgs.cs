using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Framework.Document.Events
{
    public class DirtyFlagChangedEventArgs : EventArgs
    {
        public bool DirtyFlag { get; private set; }

        public DirtyFlagChangedEventArgs(bool DirtyFlag)
        {
            this.DirtyFlag = DirtyFlag;
        }
    }
}
