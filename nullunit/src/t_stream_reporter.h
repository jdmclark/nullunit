// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_STREAM_REPORTER_H_INCLUDED_
#define _T_STREAM_REPORTER_H_INCLUDED_

#include "nullunit/internal/t_reporter.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

namespace NullUnit
{
	class StreamReporter : public Reporter
	{
		std::ostream& stream;

		std::unordered_map<std::string, unsigned int> suiteSuccesses;
		std::unordered_map<std::string, unsigned int> suiteFailures;

		unsigned int packageSuccesses;
		unsigned int packageFailures;

	private:
		void AddSuccess(const std::string& suite_name);
		void AddFailure(const std::string& suite_name);

	public:
		StreamReporter(std::ostream& s);

		void ListBegin();
		void ListEnd();

		void ListEntrySuite(const std::string& suite_name,
			const std::string& filename, int linenumber);
		void ListEntryCase(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int linenumber);

		void ReportBegin();
		void ReportEnd();

		void SuiteBegin(const std::string& suite_name);
		void SuiteEnd(const std::string& suite_name);

		void CaseBegin(const std::string& suite_name, const std::string& case_name);
		void CaseEnd(const std::string& suite_name, const std::string& case_name);

		void CasePass(const std::string& suite_name, const std::string& case_name);
		void CaseFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		void CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& what, const std::string& filename, int lineNumber);
		void CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
		void CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		void CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		
		void FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
		void FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
	};
}

#endif // _T_STREAM_REPORTER_H_INCLUDED_
