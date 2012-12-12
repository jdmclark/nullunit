// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <string>
#include <algorithm>

#include "t_gui_reporter.h"
#include "t_strings.h"

NullUnit::GuiReporter::GuiReporter(std::ostream& s)	: stream(s)
{
	return;
}

void NullUnit::GuiReporter::PrepareMessage(std::string& message)
{
	std::replace(message.begin(), message.end(), '\n', ' ');
}

void NullUnit::GuiReporter::ReportCaseFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	std::string preparedMessage(reason);
	PrepareMessage(preparedMessage);

	stream << "CASE_FAIL" << delim << suite_name << delim << case_name << delim << preparedMessage
		<< delim << filename << delim << lineNumber << std::endl;
}

void NullUnit::GuiReporter::ListBegin()
{
	stream << "NULLUNIT" << std::endl;
	stream << "LIST_BEGIN" << std::endl;
}

void NullUnit::GuiReporter::ListEnd()
{
	stream << "LIST_END" << std::endl;
}

void NullUnit::GuiReporter::ListEntrySuite(const std::string& suite_name,
	const std::string& filename, int lineNumber)
{
	stream << "LIST_SUITE" << delim << suite_name << delim << filename << delim << lineNumber << std::endl;
}

void NullUnit::GuiReporter::ListEntryCase(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	stream << "LIST_CASE" << delim << suite_name << delim << case_name << delim <<
		filename << delim << lineNumber << std::endl;
}

void NullUnit::GuiReporter::ReportBegin()
{
	stream << "NULLUNIT" << std::endl;
	stream << "REPORT_BEGIN" << std::endl;
}

void NullUnit::GuiReporter::ReportEnd()
{
	stream << "REPORT_END" << std::endl;
}

void NullUnit::GuiReporter::SuiteBegin(const std::string& suite_name)
{
	stream << "SUITE_BEGIN" << delim << suite_name << std::endl;
}

void NullUnit::GuiReporter::SuiteEnd(const std::string& suite_name)
{
	stream << "SUITE_END" << delim << suite_name << std::endl;
}

void NullUnit::GuiReporter::CaseBegin(const std::string& suite_name, const std::string& case_name)
{
	stream << "CASE_BEGIN" << delim << suite_name << delim << case_name << std::endl;
}

void NullUnit::GuiReporter::CaseEnd(const std::string& suite_name, const std::string& case_name)
{
	stream << "CASE_END" << delim << suite_name << delim << case_name << std::endl;
}

void NullUnit::GuiReporter::CasePass(const std::string& suite_name, const std::string& case_name)
{
	stream << "CASE_PASS" << delim << suite_name << delim << case_name << std::endl;
}

void NullUnit::GuiReporter::CaseFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::GuiReporter::CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& what, const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, Strings::MakeUnhandledStdExceptionString(what), filename, lineNumber);
}

void NullUnit::GuiReporter::CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, Strings::UnhandledException, filename, lineNumber);
}

void NullUnit::GuiReporter::CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::GuiReporter::CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::GuiReporter::FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, Strings::FixtureSetupFailure, filename, lineNumber);
}

void NullUnit::GuiReporter::FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	ReportCaseFail(suite_name, case_name, Strings::FixtureTeardownFailure, filename, lineNumber);
}
