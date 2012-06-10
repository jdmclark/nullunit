// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include "tt_mock_reporter.h"

NullUnitTest::MockReporter::MockReporter()
{
	ListBeginCalled = 0;
	ListEndCalled = 0;
	ListEntrySuiteCalled = 0;
	ListEntryCaseCalled = 0;
	ReportBeginCalled = 0;
	ReportEndCalled = 0;
	SuiteBeginCalled = 0;
	SuiteEndCalled = 0;
	CaseBeginCalled = 0;
	CaseEndCalled = 0;
	CasePassCalled = 0;
	CaseFailCalled = 0;
	CaseStdExceptionFailCalled = 0;
	CaseUnhandledExceptionFailCalled = 0;
	CaseAssertionFailCalled = 0;
	CaseExpectationFailCalled = 0;
	FixtureSetupFailCalled = 0;
	FixtureTeardownFailCalled = 0;
}

NullUnitTest::MockReporter::~MockReporter()
{
	return;
}

void NullUnitTest::MockReporter::ListBegin()
{
	++ListBeginCalled;
}

void NullUnitTest::MockReporter::ListEnd()
{
	++ListEndCalled;
}

void NullUnitTest::MockReporter::ListEntrySuite(const std::string& suite_name,
	const std::string& filename, int linenumber)
{
	++ListEntrySuiteCalled;
}

void NullUnitTest::MockReporter::ListEntryCase(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int linenumber)
{
	++ListEntryCaseCalled;
}

void NullUnitTest::MockReporter::ReportBegin()
{
	++ReportBeginCalled;
}

void NullUnitTest::MockReporter::ReportEnd()
{
	++ReportEndCalled;
}

void NullUnitTest::MockReporter::SuiteBegin(const std::string& suite_name)
{
	++SuiteBeginCalled;
}

void NullUnitTest::MockReporter::SuiteEnd(const std::string& suite_name)
{
	++SuiteEndCalled;
}

void NullUnitTest::MockReporter::CaseBegin(const std::string& suite_name, const std::string& case_name)
{
	++CaseBeginCalled;
}

void NullUnitTest::MockReporter::CaseEnd(const std::string& suite_name, const std::string& case_name)
{
	++CaseEndCalled;
}

void NullUnitTest::MockReporter::CasePass(const std::string& suite_name, const std::string& case_name)
{
	++CasePassCalled;
}

void NullUnitTest::MockReporter::CaseFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	++CaseFailCalled;
}

void NullUnitTest::MockReporter::CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& what, const std::string& filename, int lineNumber)
{
	++CaseStdExceptionFailCalled;
}

void NullUnitTest::MockReporter::CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	++CaseUnhandledExceptionFailCalled;
}

void NullUnitTest::MockReporter::CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	++CaseAssertionFailCalled;
}

void NullUnitTest::MockReporter::CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	++CaseExpectationFailCalled;
}

void NullUnitTest::MockReporter::FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	++FixtureSetupFailCalled;
}

void NullUnitTest::MockReporter::FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	++FixtureTeardownFailCalled;
}
