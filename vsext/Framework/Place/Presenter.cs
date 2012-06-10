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
using NullUnit.Framework.Event;

namespace NullUnit.Framework.Place
{
    public abstract class Presenter : IPresenter
    {
        public abstract void Start(IAcceptsOneControl viewFrame, IEventBus eventBus);

        public virtual void Stop()
        {
            return;
        }

        public virtual bool CanStop
        {
            get
            {
                return true;
            }
        }
    }
}
