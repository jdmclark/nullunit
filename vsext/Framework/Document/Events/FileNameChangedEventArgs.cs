using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Framework.Document.Events
{
    public class FileNameChangedEventArgs : EventArgs
    {
        public string FileName { get; private set; }

        public FileNameChangedEventArgs(string FileName)
        {
            this.FileName = FileName;
        }
    }
}
