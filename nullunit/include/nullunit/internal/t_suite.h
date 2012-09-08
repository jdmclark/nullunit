// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_SUITE_H_INCLUDED_
#define _T_SUITE_H_INCLUDED_

namespace NullUnit
{
	class Suite
	{
	public:
		virtual ~Suite() { }

		virtual CaseVector& GetCaseFactories() = 0;
		virtual CaseMap& GetCaseFactoryMap() = 0;
	};
}

#endif // _T_SUITE_H_INCLUDED_
