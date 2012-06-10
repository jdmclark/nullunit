using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Framework.Document.Events
{
    public class RedoStackDepthChangedEventArgs : EventArgs
    {
        public int Depth { get; private set; }

        public RedoStackDepthChangedEventArgs(int Depth)
        {
            this.Depth = Depth;
        }
    }
}
