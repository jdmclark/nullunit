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
    public class ChildEventBus : IEventBus
    {
        IEventBus parentEventBus;

        List<IEventRegistration> eventRegistrations = new List<IEventRegistration>();

        public ChildEventBus(IEventBus parentEventBus)
        {
            this.parentEventBus = parentEventBus;
        }

        public IEventRegistration AddHandler<T>(EventHandler<T> handler) where T : EventArgs
        {
            IEventRegistration eventRegistration = parentEventBus.AddHandler(handler);

            eventRegistrations.Add(eventRegistration);
            return eventRegistration;
        }

        public void RemoveHandler<T>(EventHandler<T> handler) where T : EventArgs
        {
            parentEventBus.RemoveHandler(handler);
        }

        public void FireEvent<T>(object sender, T e) where T : EventArgs
        {
            parentEventBus.FireEvent(sender, e);
        }

        public void RemoveAllHandlers()
        {
            foreach (IEventRegistration eventRegistration in eventRegistrations)
            {
                eventRegistration.Cancel();
            }
        }
    }
}
