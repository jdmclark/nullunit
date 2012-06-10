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
using NullUnit.Framework;
using NullUnit.Framework.Event;
using NullUnit.Runner.Events.State;
using NullUnit.Runner.Properties;

namespace NullUnit.Runner.Empty
{
    class EmptyPresenter : Presenter
    {
        EmptyPlace place;
        Services services;

        public EmptyPresenter(EmptyPlace place, Services services)
        {
            this.place = place;
            this.services = services;
        }

        public override void Start(IAcceptsOneControl viewFrame, IEventBus eventBus)
        {
            viewFrame.Control = null;

            eventBus.FireEvent(this, new PageTitleEventArgs(Resources.MainWindowDefaultTitle));
            eventBus.FireEvent(this, new StatusEventArgs(Resources.StatusEmpty, false, 0.0));
            eventBus.FireEvent(this, new CommandEnableEventArgs(false, false));
            eventBus.FireEvent(this, new TestStateEventArgs(TestState.Nothing));
        }
    }
}
