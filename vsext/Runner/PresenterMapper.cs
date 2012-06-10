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

namespace NullUnit.Runner
{
    class PresenterMapper : IPresenterMapper
    {
        Services services;

        public PresenterMapper(Services services)
        {
            this.services = services;
        }

        public IPresenter GetPresenter(IPlace place)
        {
            if (place is Empty.EmptyPlace)
            {
                return new Empty.EmptyPresenter((Empty.EmptyPlace)place, services);
            }
            else if (place is Test.TestPlace)
            {
                return new Test.TestPresenter((Test.TestPlace)place, services);
            }
            else
            {
                throw new ArgumentException();
            }
        }
    }
}
