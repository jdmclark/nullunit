// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <sstream>
#include <string>
#include "t_strings.h"

std::string NullUnit::Strings::MakeIllegalArgumentString(const std::string& arg)
{
	std::stringstream ss;
	ss << "Error: Illegal argument " << arg;
	return ss.str();
}

std::string NullUnit::Strings::MakeInvalidSuiteNameString(const std::string& suitename)
{
	std::stringstream ss;
	ss << "Error: No suite exists with name \'" << suitename << "\'";
	return ss.str();
}

std::string NullUnit::Strings::MakeInvalidCaseNameString(const std::string& suitename, const std::string& casename)
{
	std::stringstream ss;
	ss << "Error: No case exists with name \'" << suitename << "." << casename << "\'";
	return ss.str();
}

std::string NullUnit::Strings::MakeTotalTestsFailedString(int failcount)
{
	std::stringstream ss;
	ss << "Tests failed: " << failcount;
	return ss.str();
}

std::string NullUnit::Strings::MakeTotalTestsPassedString(int passcount)
{
	std::stringstream ss;
	ss << "Test cases passed: " << passcount;
	return ss.str();
}

std::string NullUnit::Strings::MakeCaseFailedLineString(const std::string& filename, int linenumber, const std::string& suitename,
														const std::string& casename, const std::string& reason)
{
	std::stringstream ss;
	ss << filename << "(" << linenumber << "): " << suitename << "::" << casename << " failed: " << reason;
	return ss.str();
}

std::string NullUnit::Strings::MakeSuiteFailedLineString(const std::string& filename, int linenumber, const std::string& suitename,
														 const std::string& reason)
{
	std::stringstream ss;
	ss << filename << "(" << linenumber << "): Suite " << suitename << " failed: " << reason;
	return ss.str();
}

std::string NullUnit::Strings::MakeSuiteFailedCasesString(const std::string& suitename, int failcount)
{
	std::stringstream ss;
	ss << "Suite " << suitename << " failed: " << failcount << " cases";
	return ss.str();
}

std::string NullUnit::Strings::MakeUnhandledStdExceptionString(const std::string& what)
{
	std::stringstream ss;
	ss << "Unhandled exception: " << what;
	return ss.str();
}
