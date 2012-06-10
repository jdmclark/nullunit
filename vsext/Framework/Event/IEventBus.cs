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

namespace NullUnit.Framework.Event
{
    public interface IEventBus
    {
        IEventRegistration AddHandler<T>(EventHandler<T> handler) where T : EventArgs;
        void RemoveHandler<T>(EventHandler<T> handler) where T : EventArgs;

        void FireEvent<T>(object sender, T e) where T : EventArgs;
    }
}
