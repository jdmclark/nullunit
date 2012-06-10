using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NullUnit.Framework.Document.Events;

namespace NullUnit.Framework.Document
{
    public interface IDocument
    {
        event EventHandler<DirtyFlagChangedEventArgs> DirtyFlagChanged;
        event EventHandler<FileNameChangedEventArgs> FileNameChanged;
        event EventHandler<UndoStackDepthChangedEventArgs> UndoStackDepthChanged;
        event EventHandler<RedoStackDepthChangedEventArgs> RedoStackDepthChanged;

        string FileName { get; set; }
        bool DirtyFlag { get; }

        void CommitAction(IAction action);
        void Undo();
        void Redo();

        void Serialize();
        void Deserialize(string FileName);
    }
}
