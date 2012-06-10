// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <nullunit/nullunit.h>

namespace NullUnitTest
{
	BeginSuite(CaseOrderSuite);

	Case(Case1) { }

	Case(ValidateCaseOrder)
	{
		NullUnit::SuiteMap& factories = NullUnit::SuiteRegistry::Get().Factories;

		auto it = factories.find("CaseOrderSuite");
		Test_Assert_Neq(it, factories.end());

		auto suite = it->second->CreateSuite();

		NullUnit::CaseVector& cases = suite->GetCaseFactories();
		
		Test_Assert_Eq(cases[0].first, "Case1");
		Test_Assert_Eq(cases[1].first, "ValidateCaseOrder");
		Test_Assert_Eq(cases[2].first, "Case3");
		Test_Assert_Eq(cases[3].first, "Case5");
		Test_Assert_Eq(cases[4].first, "Case2");
		Test_Assert_Eq(cases[5].first, "Case6");
	}

	Case(Case3) { }

	Case(Case5) { }

	Case(Case2) { }

	Case(Case6) { }

	EndSuite(CaseOrderSuite);
}
