using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NullUnit.Framework.Document.Events;

namespace NullUnit.Framework.Document
{
    public abstract class AbstractDocument : IDocument
    {
        public event EventHandler<DirtyFlagChangedEventArgs> DirtyFlagChanged;
        public event EventHandler<FileNameChangedEventArgs> FileNameChanged;
        public event EventHandler<UndoStackDepthChangedEventArgs> UndoStackDepthChanged;
        public event EventHandler<RedoStackDepthChangedEventArgs> RedoStackDepthChanged;

        private Stack<IAction> undoStack = new Stack<IAction>();
        private Stack<IAction> redoStack = new Stack<IAction>();

        private string iFileName;
        public string FileName
        {
            get
            {
                return iFileName;
            }

            set
            {
                if (iFileName != value)
                {
                    iFileName = value;

                    if (FileNameChanged != null)
                    {
                        FileNameChanged.Invoke(this, new FileNameChangedEventArgs(iFileName));
                    }
                }
            }
        }

        private bool iDirtyFlag;
        public bool DirtyFlag
        {
            get
            {
                return iDirtyFlag;
            }

            private set
            {
                if (iDirtyFlag != value)
                {
                    iDirtyFlag = value;

                    if (DirtyFlagChanged != null)
                    {
                        DirtyFlagChanged.Invoke(this, new DirtyFlagChangedEventArgs(iDirtyFlag));
                    }
                }
            }
        }

        private void FireUndoStackDepthChanged()
        {
            if (UndoStackDepthChanged != null)
            {
                UndoStackDepthChanged.Invoke(this, new UndoStackDepthChangedEventArgs(undoStack.Count));
            }
        }

        private void FireRedoStackDepthChanged()
        {
            if (RedoStackDepthChanged != null)
            {
                RedoStackDepthChanged.Invoke(this, new RedoStackDepthChangedEventArgs(redoStack.Count));
            }
        }

        public void CommitAction(IAction action)
        {
            action.Execute();

            undoStack.Push(action);
            FireUndoStackDepthChanged();

            redoStack.Clear();
            FireRedoStackDepthChanged();

            DirtyFlag = true;
        }

        public void Undo()
        {
            if (undoStack.Count > 0)
            {
                IAction action = undoStack.Pop();
                FireUndoStackDepthChanged();

                action.Reverse();

                redoStack.Push(action);
                FireRedoStackDepthChanged();

                DirtyFlag = true;
            }
        }

        public void Redo()
        {
            if (redoStack.Count > 0)
            {
                IAction action = redoStack.Pop();
                FireRedoStackDepthChanged();

                action.Execute();

                undoStack.Push(action);
                FireUndoStackDepthChanged();

                DirtyFlag = true;
            }
        }

        public abstract void Serialize();
        public abstract void Deserialize(string FileName);
    }
}
