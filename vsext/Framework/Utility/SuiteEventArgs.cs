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

namespace NullUnit.Framework.Utility
{
    public class SuiteEventArgs : EventArgs
    {
        public string Suite { get; private set; }

        public SuiteEventArgs(string Suite)
        {
            this.Suite = Suite;
        }
    }
}
