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
    public class PlaceController
    {
        IEventBus eventBus;
        IPresenterMapper presenterMapper;
        IAcceptsOneControl viewFrame;

        ChildEventBus currentChildEventBus;
        IPresenter currentPresenter;

        public PlaceController(IEventBus eventBus, IPresenterMapper presenterMapper,
            IAcceptsOneControl viewFrame)
        {
            this.eventBus = eventBus;
            this.presenterMapper = presenterMapper;
            this.viewFrame = viewFrame;
        }

        public void GoTo(IPlace place)
        {
            if (currentPresenter != null)
            {
                if (!currentPresenter.CanStop)
                {
                    // Abort
                    return;
                }

                currentPresenter.Stop();
            }

            if (currentChildEventBus != null)
            {
                currentChildEventBus.RemoveAllHandlers();
            }

            currentChildEventBus = new ChildEventBus(eventBus);
            currentPresenter = presenterMapper.GetPresenter(place);

            if (currentPresenter != null)
            {
                currentPresenter.Start(viewFrame, currentChildEventBus);
            }
        }
    }
}
