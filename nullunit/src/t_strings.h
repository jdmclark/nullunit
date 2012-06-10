// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_STRINGS_H_INCLUDED_
#define _T_STRINGS_H_INCLUDED_

namespace NullUnit
{
	namespace Strings
	{
		// Interface messages
		static const char* IllegalArgument = "Error: Illegal argument %d";
		static const char* MultipleOutputTypes = "Error: Multiple output types selected";
		static const char* InvalidSuiteName = "Error: No suite exists with name \'%s\'";
		static const char* InvalidCaseName = "Error: No case exists with name \'%s.%s\'";

		static const char* CaseBeforeSuite = "Internal error: Case visited before parent suite";

		static const char* RunningTests = "Running unit tests";

		static const char* TotalTestsFailed = "Tests failed: %d";
		static const char* TotalTestsPassed = "Test cases passed: %d";

		// Stream report printer messages
		static const char* CaseFailedLine = "%s(%d): %s::%s failed: %s";
		static const char* SuiteFailedLine = "%s(%d): Suite %s failed: %s";
		static const char* SuiteFailedCases = "Suite %s failed: %d cases";

		static const char* UnhandledException = "Unhandled exception";
		static const char* UnhandledStdException = "Unhandled exception: %s";
		static const char* SuiteCreateFailure = "Creation failed";
		static const char* FixtureSetupFailure = "Fixture setup failed";
		static const char* FixtureTeardownFailure = "Fixture teardown failed";

		static const char* XmlListSchemaUri = "http://nullptr.ca/nullunit/list_schema.xsd";
		static const char* XmlReportSchemaUri = "http://nullptr.ca/nullunit/report_schema.xsd";
	}
}

#endif // _T_STRINGS_H_INCLUDED_
