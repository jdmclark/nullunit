// Copyright (c) 2011-2012, Jonathan Clark
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
		static const char* MultipleOutputTypes = "Error: Multiple output types selected";
		static const char* CaseBeforeSuite = "Internal error: Case visited before parent suite";
		static const char* RunningTests = "Running unit tests";

		// Stream report printer messages
		static const char* UnhandledException = "Unhandled exception";
		static const char* SuiteCreateFailure = "Creation failed";
		static const char* FixtureSetupFailure = "Fixture setup failed";
		static const char* FixtureTeardownFailure = "Fixture teardown failed";

		static const char* XmlListSchemaUri = "http://nullptr.ca/files/nullunit_list_schema.xsd";
		static const char* XmlReportSchemaUri = "http://nullptr.ca/files/nullunit_report_schema.xsd";

		std::string MakeIllegalArgumentString(const std::string& arg);
		std::string MakeInvalidSuiteNameString(const std::string& suitename);
		std::string MakeInvalidCaseNameString(const std::string& suitename, const std::string& casename);

		std::string MakeTotalTestsFailedString(int failcount);
		std::string MakeTotalTestsPassedString(int passcount);

		std::string MakeCaseFailedLineString(const std::string& filename, int linenumber, const std::string& suitename, const std::string& casename, const std::string& reason);
		std::string MakeSuiteFailedLineString(const std::string& filename, int linenumber, const std::string& suitename, const std::string& reason);
		std::string MakeSuiteFailedCasesString(const std::string& suitename, int failcount);

		std::string MakeUnhandledStdExceptionString(const std::string& what);
	}
}

#endif // _T_STRINGS_H_INCLUDED_
