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
using NullUnit.Framework;

namespace NullUnit.Runner.Test
{
    interface ITestView : IProvidesOneControl
    {
        ITestPresenter Presenter { set; }

        IEnumerable<string> SelectedTests { get; }

        void Clear();
        void AddCaseResult(string suiteName, string caseName, string result,
            string filename, int lineNumber, TestState state);
        void AddSuite(string suiteName);
        void SetCaseState(string suiteName, string caseName, TestState state);
    }
}
