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
    class CommandEnableEventArgs : EventArgs
    {
        public bool? RunAllEnabled { get; private set; }
        public bool? RunSelectedEnabled { get; private set; }

        public CommandEnableEventArgs(bool? RunAllEnabled, bool? RunSelectedEnabled)
        {
            this.RunAllEnabled = RunAllEnabled;
            this.RunSelectedEnabled = RunSelectedEnabled;
        }
    }
}
