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
	class FrameworkTestFixture : public NullUnit::Fixture
	{
	protected:
		std::shared_ptr<NullUnit::Reporter> originalReporter;
		std::shared_ptr<MockReporter> mockReporter;

	public:
		FrameworkTestFixture()
		{
			originalReporter = NullUnit::Test_Reporter;
			mockReporter = std::make_shared<MockReporter>();
		}
	};

	BeginSuiteFixture(FrameworkTest, FrameworkTestFixture);

	Case(Empty)
	{
	}

	Case(VerifyNames)
	{
		Test_Expect_Eq(::NullUnit::Test_Suite_Name, std::string("FrameworkTest"));
		Test_Expect_Eq(::NullUnit::Test_Case_Name, std::string("VerifyNames"));
	}

	EndSuite(FrameworkTest);
}
