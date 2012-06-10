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
    public class SimpleEventBus : IEventBus
    {
        Dictionary<Type, Object> eventHandlers = new Dictionary<Type, object>();

        public IEventRegistration AddHandler<T>(EventHandler<T> handler) where T : EventArgs
        {
            object ehObj;
            if (eventHandlers.TryGetValue(typeof(T), out ehObj) && ehObj is EventHandler<T>)
            {
                EventHandler<T> eh = ehObj as EventHandler<T>;
                eh += handler;
                eventHandlers[typeof(T)] = eh;
            }
            else
            {
                eventHandlers[typeof(T)] = handler;
            }

            return new EventRegistration<T>(this, handler);
        }

        public void RemoveHandler<T>(EventHandler<T> handler) where T : EventArgs
        {
            object ehObj;
            if (eventHandlers.TryGetValue(typeof(T), out ehObj) && ehObj is EventHandler<T>)
            {
                EventHandler<T> eh = ehObj as EventHandler<T>;
                eh -= handler;
                eventHandlers[typeof(T)] = eh;
            }

            return;
        }

        public void FireEvent<T>(object sender, T e) where T : EventArgs
        {
            object ehObj;
            if (eventHandlers.TryGetValue(typeof(T), out ehObj) && ehObj is EventHandler<T>)
            {
                EventHandler<T> eh = ehObj as EventHandler<T>;
                eh.Invoke(sender, e);
            }

            return;
        }
    }
}
