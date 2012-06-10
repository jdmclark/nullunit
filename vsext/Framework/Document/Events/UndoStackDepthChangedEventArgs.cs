using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Framework.Document.Events
{
    public class UndoStackDepthChangedEventArgs : EventArgs
    {
        public int Depth { get; private set; }

        public UndoStackDepthChangedEventArgs(int Depth)
        {
            this.Depth = Depth;
        }
    }
}
