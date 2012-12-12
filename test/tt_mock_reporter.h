// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <nullunit/internal/t_reporter.h>

#ifndef _T_MOCK_REPORTER_H_INCLUDED_
#define _T_MOCK_REPORTER_H_INCLUDED_

namespace NullUnitTest
{
	class MockReporter : public NullUnit::Reporter
	{
	public:
		MockReporter();
		virtual ~MockReporter();

		int ListBeginCalled;
		int ListEndCalled;
		int ListEntrySuiteCalled;
		int ListEntryCaseCalled;
		int ReportBeginCalled;
		int ReportEndCalled;
		int SuiteBeginCalled;
		int SuiteEndCalled;
		int CaseBeginCalled;
		int CaseEndCalled;
		int CasePassCalled;
		int CaseFailCalled;
		int CaseStdExceptionFailCalled;
		int CaseUnhandledExceptionFailCalled;
		int CaseAssertionFailCalled;
		int CaseExpectationFailCalled;
		int FixtureSetupFailCalled;
		int FixtureTeardownFailCalled;

		virtual void ListBegin();
		virtual void ListEnd();

		virtual void ListEntrySuite(const std::string& suite_name,
			const std::string& filename, int linenumber);
		virtual void ListEntryCase(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int linenumber);

		virtual void ReportBegin();
		virtual void ReportEnd();

		virtual void SuiteBegin(const std::string& suite_name);
		virtual void SuiteEnd(const std::string& suite_name);

		virtual void CaseBegin(const std::string& suite_name, const std::string& case_name);
		virtual void CaseEnd(const std::string& suite_name, const std::string& case_name);

		virtual void CasePass(const std::string& suite_name, const std::string& case_name);
		virtual void CaseFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		virtual void CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& what, const std::string& filename, int lineNumber);
		virtual void CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
		virtual void CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		virtual void CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);
		
		virtual void FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
		virtual void FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
			const std::string& filename, int lineNumber);
	};
}

#endif // _T_MOCK_REPORTER_H_INCLUDED_
