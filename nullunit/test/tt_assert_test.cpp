// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <nullunit/nullunit.h>

namespace NullUnitTest
{
	BeginSuite(AssertTest);

	Case(Base)
	{
		try
		{
			Test_Assert(false);
		}
		catch(...)
		{
			Test_Assert(true);
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Always)
	{
		try
		{
			Test_Assert_Always("Test");
		}
		catch(...)
		{
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Eq)
	{
		try
		{
			Test_Assert_Eq(1, 0);
		}
		catch(...)
		{
			Test_Assert_Eq(1, 1);
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Gt)
	{
		try
		{
			Test_Assert_Gt(0, 1);
		}
		catch(...)
		{
			Test_Assert_Gt(1, 0);

			try
			{
				Test_Assert_Gt(0, 0);
			}
			catch(...)
			{
				return;
			}
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Lt)
	{
		try
		{
			Test_Assert_Lt(1, 0);
		}
		catch(...)
		{
			Test_Assert_Lt(0, 1);

			try
			{
				Test_Assert_Lt(0, 0);
			}
			catch(...)
			{
				return;
			}
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Gte)
	{
		try
		{
			Test_Assert_Gte(0, 1);
		}
		catch(...)
		{
			Test_Assert_Gte(1, 0);
			Test_Assert_Gte(1, 1);
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Lte)
	{
		try
		{
			Test_Assert_Lte(1, 0);
		}
		catch(...)
		{
			Test_Assert_Lte(0, 1);
			Test_Assert_Lte(1, 1);
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	Case(Neq)
	{
		try
		{
			Test_Assert_Neq(1, 1);
		}
		catch(...)
		{
			Test_Assert_Neq(1, 0);
			return;
		}

		Test_Assert_Always("Assertion failed.");
	}

	EndSuite(AssertTest);
}
