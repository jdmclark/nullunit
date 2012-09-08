// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_FIXTURE_H_INCLUDED_
#define _T_FIXTURE_H_INCLUDED_

#include "nullunit/internal/t_case.h"

namespace NullUnit
{
	/// @brief The base type for all test fixtures.
	class Fixture : public Case
	{
	public:
		virtual ~Fixture();

		virtual void Setup();
		virtual void Teardown();
	};
}

#endif // _T_FIXTURE_H_INCLUDED_
