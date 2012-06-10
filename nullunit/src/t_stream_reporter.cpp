// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <string>

#include <boost/format.hpp>

#include "t_stream_reporter.h"
#include "t_strings.h"

NullUnit::StreamReporter::StreamReporter(std::ostream& s)
	: stream(s), packageSuccesses(0), packageFailures(0)
{
	return;
}

void NullUnit::StreamReporter::AddSuccess(const std::string& suite_name)
{
	++packageSuccesses;
	++suiteSuccesses[suite_name];
}

void NullUnit::StreamReporter::AddFailure(const std::string& suite_name)
{
	++packageFailures;
	++suiteFailures[suite_name];
}

void NullUnit::StreamReporter::ListBegin()
{
	return;
}

void NullUnit::StreamReporter::ListEnd()
{
	return;
}

void NullUnit::StreamReporter::ListEntrySuite(const std::string& suite_name,
	const std::string& filename, int lineNumber)
{
	return;
}

void NullUnit::StreamReporter::ListEntryCase(const std::string& suite_name,
	const std::string& case_name, const std::string& filename, int lineNumber)
{
	return;
}

void NullUnit::StreamReporter::ReportBegin()
{
	stream << Strings::RunningTests << std::endl;
}

void NullUnit::StreamReporter::ReportEnd()
{
	stream << boost::str(boost::format(Strings::TotalTestsPassed) % packageSuccesses) << std::endl;

	if(packageFailures > 0)
	{
		stream << boost::str(boost::format(Strings::TotalTestsFailed) % packageFailures) << std::endl;
	}
}

void NullUnit::StreamReporter::SuiteBegin(const std::string& suite_name)
{
	return;
}

void NullUnit::StreamReporter::SuiteEnd(const std::string& suite_name)
{
	unsigned int s_failure_ct = suiteFailures[suite_name];

	if(s_failure_ct > 0)
	{
		stream << boost::str(boost::format(Strings::SuiteFailedCases)
			% suite_name % s_failure_ct) << std::endl;
	}
}

void NullUnit::StreamReporter::CaseBegin(const std::string& suite_name, const std::string& case_name)
{
	return;
}

void NullUnit::StreamReporter::CaseEnd(const std::string& suite_name, const std::string& case_name)
{
	return;
}

void NullUnit::StreamReporter::CasePass(const std::string& suite_name, const std::string& case_name)
{
	AddSuccess(suite_name);
}

void NullUnit::StreamReporter::CaseFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % reason) << std::endl;
}

void NullUnit::StreamReporter::CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& what, const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name
		% boost::str(boost::format(Strings::UnhandledStdException) % what)) << std::endl;
}

void NullUnit::StreamReporter::CaseUnhandledExceptionFail(const std::string& suite_name,
	const std::string& case_name, const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % Strings::UnhandledException) << std::endl;
}

void NullUnit::StreamReporter::CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % reason) << std::endl;
}

void NullUnit::StreamReporter::CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % reason) << std::endl;
}

void NullUnit::StreamReporter::FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % Strings::FixtureSetupFailure) << std::endl;
}

void NullUnit::StreamReporter::FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	AddFailure(suite_name);
	stream << boost::str(boost::format(Strings::CaseFailedLine)
		% filename % lineNumber % suite_name % case_name % Strings::FixtureTeardownFailure) << std::endl;
}
