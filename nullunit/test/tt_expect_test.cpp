// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <nullunit/nullunit.h>
#include "tt_mock_reporter.h"

namespace NullUnitTest
{
	class ExpectTestFixture : public NullUnit::Fixture
	{
	protected:
		std::shared_ptr<NullUnit::Reporter> originalReporter;
		std::shared_ptr<MockReporter> mockReporter;

	public:
		ExpectTestFixture()
		{
			originalReporter = NullUnit::Test_Reporter;
			mockReporter = std::make_shared<MockReporter>();
		}
	};

	BeginSuiteFixture(ExpectTest, ExpectTestFixture);

	Case(Base)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect(false);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	Case(Always)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Always("Meaningful message");

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	Case(Eq)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Eq(1, 0);
		Test_Expect_Eq(1, 1);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	Case(Gt)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Gt(0, 1);
		Test_Expect_Gt(1, 0);
		Test_Expect_Gt(0, 0);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 2);
	}

	Case(Lt)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Lt(1, 0);
		Test_Expect_Lt(0, 1);
		Test_Expect_Lt(0, 0);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 2);
	}

	Case(Gte)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Gte(0, 1);
		Test_Expect_Gte(1, 0);
		Test_Expect_Gte(1, 1);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	Case(Lte)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Lte(1, 0);
		Test_Expect_Lte(0, 1);
		Test_Expect_Lte(1, 1);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	Case(Neq)
	{
		// Exchange out the original test reporter.
		NullUnit::Test_Reporter = mockReporter;

		Test_Expect_Neq(1, 1);
		Test_Expect_Neq(1, 0);

		NullUnit::Test_Reporter = originalReporter;

		Test_Assert(!NullUnit::Test_Passing);
		NullUnit::Test_Passing = true;

		Test_Assert_Eq(mockReporter->CaseExpectationFailCalled, 1);
	}

	EndSuite(ExpectTest);
}
