// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_REPORTER_H_INCLUDED_
#define _T_REPORTER_H_INCLUDED_

#include <string>

namespace NullUnit
{
	class Reporter
	{
	public:
		virtual ~Reporter() { }

		virtual void ListBegin() = 0;
		virtual void ListEnd() = 0;

		virtual void ListEntrySuite(const std::string& suite_name,
			const std::string& filename, int linenumber) = 0;
		virtual void ListEntryCase(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int linenumber) = 0;

		virtual void ReportBegin() = 0;
		virtual void ReportEnd() = 0;

		virtual void SuiteBegin(const std::string& suite_name) = 0;
		virtual void SuiteEnd(const std::string& suite_name) = 0;

		virtual void CaseBegin(const std::string& suite_name, const std::string& case_name) = 0;
		virtual void CaseEnd(const std::string& suite_name, const std::string& case_name) = 0;

		virtual void CasePass(const std::string& suite_name, const std::string& case_name) = 0;
		virtual void CaseFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber) = 0;
		virtual void CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& what, const std::string& filename, int lineNumber) = 0;
		virtual void CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber) = 0;
		virtual void CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber) = 0;
		virtual void CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber) = 0;
		
		virtual void FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber) = 0;
		virtual void FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber) = 0;
	};
}

#endif // _T_REPORTER_H_INCLUDED_
