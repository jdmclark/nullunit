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
    class BackgroundRunnerParameters
    {
        public string ExePath { get; private set; }
        public bool ListOnly { get; private set; }
        public IEnumerable<string> Cases { get; private set; }

        public BackgroundRunnerParameters(string ExePath, bool ListOnly, IEnumerable<string> Cases)
        {
            this.ExePath = ExePath;
            this.ListOnly = ListOnly;
            this.Cases = Cases;
        }
    }
}
