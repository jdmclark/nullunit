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
using NullUnit.Framework.Event;
using NullUnit.Runner.Test;
using NullUnit.Framework;

namespace NullUnit.Runner
{
    class Services
    {
        public PlaceController PlaceController { get; private set; }
        public IEventBus EventBus { get; private set; }

        public ITestView TestView { get; private set; }

        public Services(IAcceptsOneControl viewFrame)
        {
            EventBus = new SimpleEventBus();
            IPresenterMapper presenterMapper = new PresenterMapper(this);
            PlaceController = new PlaceController(EventBus, presenterMapper, viewFrame);

            TestView = new TestView();
        }
    }
}
