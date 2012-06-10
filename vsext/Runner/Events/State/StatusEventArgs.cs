// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullUnit.Runner.Events.State
{
    class StatusEventArgs : EventArgs
    {
        public string Message { get; private set; }
        public bool ShowProgress { get; private set; }
        public double Progress { get; private set; }

        public StatusEventArgs(string Message, bool ShowProgress, double Progress)
        {
            this.Message = Message;
            this.ShowProgress = ShowProgress;
            this.Progress = Progress;
        }
    }
}
