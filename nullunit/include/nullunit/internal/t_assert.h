// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

/**
 * @file
 * @brief Defines common assertions used by test cases.
 */

#ifndef _T_ASSERT_H_INCLUDED_
#define _T_ASSERT_H_INCLUDED_

#include "nullunit/internal/t_exception.h"

#define BALsX(x) #x
#define BALs(x) BALsX(x)
#define BAL BALs(__LINE__)

/**
 * @brief Base assertion from which all others are implemented.
 * @param[in] x The expression to evaluate.
 * @param[in] y The message to display if x is false.
 */
#define Base_Assert(x, y)															 \
	do { if(!(x)) throw ::NullUnit::Exception(__FILE__, __LINE__, y); } while(false)

/**
 * @brief Base expected condition from which all others are implemented.
 * @param[in] x The expression to evaluate.
 * @param[in] y The message to display if x is false.
 */
#define Base_Expect(x, y)															\
	do { if(!(x)) { ::NullUnit::Test_Passing = false;								\
	::NullUnit::Test_Reporter->CaseExpectationFail(::NullUnit::Test_Suite_Name,		\
	::NullUnit::Test_Case_Name, y, __FILE__, __LINE__); } } while(false)

/**
 * @brief Simple assertion on a single expression.
 * @param[in] x The expression to evaluate.
 */
#define Test_Assert(x) Base_Assert((x), "Assertion failed")

/**
 * @brief Simple expectation on a single expression.
 * @param[in] x The expression to evaluate.
 */
#define Test_Expect(x) Base_Expect((x), "Expectation failed")

/**
 * @brief Assertion that always fails.
 * @param[in] x The message to display.
 */
#define Test_Assert_Always(x) Base_Assert(false, x)

/**
 * @brief Expectation that always fails.
 * @param[in] x The message to display.
 */
#define Test_Expect_Always(x) Base_Expect(false, x)

/**
 * @brief Assertion that fails unless both parameters are equal.
 * @param[in] x The first parameter to test.
 * @param[in] y The second parameter to test.
 */
#define Test_Assert_Eq(x, y) Base_Assert(((x) == (y)), #x " not equal to " #y)

/**
 * @brief Expectation that fails unless both parameters are equal.
 * @param[in] x The first parameter to test.
 * @param[in] y The second parameter to test.
 */
#define Test_Expect_Eq(x, y) Base_Expect(((x) == (y)), #x " not equal to " #y)

/**
 * @brief Assertion that fails unless the first parameter is greater than the second.
 * @param[in] x The parameter that must be greater.
 * @param[in] y The parameter that must be less.
 */
#define Test_Assert_Gt(x, y) Base_Assert(((x) > (y)), #x " not greater than " #y)

/**
 * @brief Expectation that fails unless the first parameter is greater than the second.
 * @param[in] x The parameter that must be greater.
 * @param[in] y The parameter that must be less.
 */
#define Test_Expect_Gt(x, y) Base_Expect(((x) > (y)), #x " not greater than " #y)

/**
 * @brief Assertion that fails unless the first parameter is less than the second.
 * @param[in] x The parameter that must be less.
 * @param[in] y The parameter that must be greater.
 */
#define Test_Assert_Lt(x, y) Base_Assert(((x) < (y)), #x " not less than " #y)

/**
 * @brief Expectation that fails unless the first parameter is less than the second.
 * @param[in] x The parameter that must be less.
 * @param[in] y The parameter that must be greater.
 */
#define Test_Expect_Lt(x, y) Base_Expect(((x) < (y)), #x " not less than " #y)

/**
 * @brief Assertion that fails unless the first parameter is greater than or equal to the second.
 * @param[in] x The parameter that must be greater than or equal.
 * @param[in] y The parameter that must be less than or equal.
 */
#define Test_Assert_Gte(x, y) Base_Assert(((x) >= (y)), #x " not greater than or equal to " #y)

/**
 * @brief Expectation that fails unless the first parameter is greater than or equal to the second.
 * @param[in] x The parameter that must be greater than or equal.
 * @param[in] y The parameter that must be less than or equal.
 */
#define Test_Expect_Gte(x, y) Base_Expect(((x) >= (y)), #x " not greater than or equal to " #y)

/**
 * @brief Assertion that fails unless the first parameter is less than or equal to the second.
 * @param[in] x The parameter that must be less than or equal.
 * @param[in] y The parameter that must be greater than or equal.
 */
#define Test_Assert_Lte(x, y) Base_Assert(((x) <= (y)), #x " not less than or equal to " #y)

/**
 * @brief Expectation that fails unless the first parameter is less than or equal to the second.
 * @param[in] x The parameter that must be less than or equal.
 * @param[in] y The parameter that must be greater than or equal.
 */
#define Test_Expect_Lte(x, y) Base_Expect(((x) <= (y)), #x " not less than or equal to " #y)

/**
 * @brief Assertion that fails unless both parameters are not equal.
 * @param[in] x The first parameter to test.
 * @param[in] y The second parameter to test.
 */
#define Test_Assert_Neq(x, y) Base_Assert(((x) != (y)), #x " is equal to " #y)

/**
 * @brief Expectation that fails unless both parameters are not equal.
 * @param[in] x The first parameter to test.
 * @param[in] y The second parameter to test.
 */
#define Test_Expect_Neq(x, y) Base_Expect(((x) != (y)), #x " is equal to " #y)

#endif // _T_ASSERT_H_INCLUDED_
