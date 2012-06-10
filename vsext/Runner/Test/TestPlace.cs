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
using NullUnit.Framework.Place;

namespace NullUnit.Runner.Test
{
    class TestPlace : IPlace
    {
        public string Filename { get; private set; }

        public TestPlace(string Filename)
        {
            this.Filename = Filename;
        }
    }
}
