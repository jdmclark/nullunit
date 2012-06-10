// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

/***************************************************
 * This file is for internal implementation details.
 * Do not add project-specific modifications.
 ***************************************************/

#ifndef _NULLUNIT_H_INCLUDED_
#define _NULLUNIT_H_INCLUDED_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

// Framework includes:
#include "nullunit/internal/t_singleton.h"
#include "nullunit/internal/t_reporter.h"
#include "nullunit/internal/t_case.h"
#include "nullunit/internal/t_casefac.h"
#include "nullunit/internal/t_casereg.h"
#include "nullunit/internal/t_suite.h"
#include "nullunit/internal/t_suitefac.h"
#include "nullunit/internal/t_suitereg.h"
#include "nullunit/internal/t_autorun.h"
#include "nullunit/internal/t_fixture.h"
#include "nullunit/internal/t_assert.h"

// Globals, needed to support assertions in subroutines and lambdas.
namespace NullUnit
{
	// Test output reporter
	extern std::shared_ptr< ::NullUnit::Reporter> Test_Reporter;

	// Name of the currently-executing suite.
	extern std::string Test_Suite_Name;

	// Name of the currently-executing case.
	extern std::string Test_Case_Name;

	// Pass/fail state of the current case.
	extern bool Test_Passing;
}

// Macro definitions:

/**
 * @brief Declares a new test suite using the specified fixture.
 * @param[in] x The name of the suite.
 * @param[in] y The typename of the fixture.
 */
#define BeginSuiteFixture(x, y)										\
class x : public ::NullUnit::Suite									\
{																	\
public:																\
	x()																\
	{																\
		::NullUnit::LockCaseRegistry< Test_Fixture >();				\
	}																\
																	\
	class Test_Fixture : public y									\
	{																\
	public:															\
		~Test_Fixture() {}

/**
 * @brief Declares a new test suite.
 * @param[in] x The name of the suite.
 */
#define BeginSuite(x) BeginSuiteFixture(x, ::NullUnit::Fixture)

/**
 * @brief Terminates the test suite.
 * @param[in] x The name of the suite.
 */
#define EndSuite(x)													\
};																	\
::NullUnit::CaseVector& GetCaseFactories()							\
{																	\
	return ::NullUnit::CaseRegistry<Test_Fixture>::Get().Factories;	\
}																	\
::NullUnit::CaseMap& GetCaseFactoryMap()							\
{																	\
	return ::NullUnit::CaseRegistry<Test_Fixture>::Get().FactoryMap;\
} };																\
::NullUnit::Autorun< ::NullUnit::RegisterSuite<x> > x##_aro(		\
	#x, __FILE__, __LINE__);

/**
 * @brief Defines a new test case.
 * @param[in] z The name of the case.
 */
#define Case(z)														\
};																	\
class z##_case;														\
struct z##_autoregister												\
{																	\
	z##_autoregister()												\
	{																\
		::NullUnit::RegisterCase< Test_Fixture, z##_case >(			\
			#z, __FILE__, __LINE__);								\
	}																\
} z##_aro;															\
class z##_case : public Test_Fixture								\
{																	\
public:																\
	void Run()

#endif // _TEST_H_INCLUDED_
