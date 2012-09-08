// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_CASE_H_INCLUDED_
#define _T_CASE_H_INCLUDED_

namespace NullUnit
{
	class Case
	{
	public:
		virtual ~Case() { }

		virtual void Run() = 0;

		virtual void Setup() = 0;
		virtual void Teardown() = 0;
	};
}

#endif // _T_CASE_H_INCLUDED_
