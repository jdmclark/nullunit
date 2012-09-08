// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include <string>

#include "nullunit/nullunit.h"
#include "t_strings.h"
#include "t_stream_reporter.h"
#include "t_gui_reporter.h"
#include "t_xml_reporter.h"
#include "t_reporter_type.h"

namespace NullUnit
{
	std::shared_ptr<NullUnit::Reporter> Test_Reporter;
	std::string Test_Suite_Name;
	std::string Test_Case_Name;
	bool Test_Passing;

	void ListCase(const std::string& suiteName, const std::string& caseName, std::shared_ptr<CaseFactory> factory)
	{
		Test_Reporter->ListEntryCase(suiteName, caseName, factory->Filename, factory->LineNumber);
	}

	void ListSuite(const std::string& suiteName, std::shared_ptr<SuiteFactory> factory)
	{
		Test_Reporter->ListEntrySuite(suiteName, factory->Filename, factory->LineNumber);

		std::shared_ptr<Suite> suite = factory->CreateSuite();
		CaseVector& caseFactories = suite->GetCaseFactories();

		for(auto jt = caseFactories.begin(); jt != caseFactories.end(); ++jt)
		{
			ListCase(suiteName, jt->first, jt->second);
		}
	}

	void ListOnlySuite(int& failures, const std::string& suiteName, const std::string& caseName, std::shared_ptr<SuiteFactory> factory)
	{
		auto suite = factory->CreateSuite();
		auto caseFac = suite->GetCaseFactoryMap().find(caseName);

		if(caseFac == suite->GetCaseFactoryMap().end())
		{
			++failures;
			std::cerr << Strings::MakeInvalidCaseNameString(suiteName, caseName) << std::endl;
		}
		else
		{
			ListCase(suiteName, caseFac->first, caseFac->second);
		}
	}

	void ListCases()
	{
		Test_Reporter->ListBegin();

		SuiteMap& factories = SuiteRegistry::Get().Factories;
		for(auto it = factories.begin(); it != factories.end(); ++it)
		{
			ListSuite(it->first, it->second);
		}

		Test_Reporter->ListEnd();
	}

	void ListOnlyCases(int& failures, const std::vector<std::pair<std::string, std::string>>& cases)
	{
		Test_Reporter->ListBegin();

		for(auto it = cases.begin(); it != cases.end(); ++it)
		{
			auto suiteFac = SuiteRegistry::Get().Factories.find(it->first);

			if(suiteFac == SuiteRegistry::Get().Factories.end())
			{
				++failures;
				std::cerr << Strings::MakeInvalidSuiteNameString(it->first) << std::endl;
			}
			else
			{
				if(it->second.empty())
				{
					ListSuite(suiteFac->first, suiteFac->second);
				}
				else
				{
					ListOnlySuite(failures, suiteFac->first, it->second, suiteFac->second);
				}
			}
		}

		Test_Reporter->ListEnd();
	}

	void RunCase(int& failures, const std::string& suiteName, const std::string& caseName, std::shared_ptr<CaseFactory> factory)
	{
		Test_Suite_Name = suiteName;
		Test_Case_Name = caseName;

		std::unique_ptr<Case> testCase(nullptr);

		// Setup case
		try
		{
			testCase = std::unique_ptr<Case>(factory->CreateCase());
			testCase->Setup();
		}
		catch(...)
		{
			Test_Reporter->FixtureSetupFail(suiteName, caseName,
				factory->Filename, factory->LineNumber);
			++failures;
			return;
		}

		// Run test case
		try
		{
			Test_Passing = true;
			testCase->Run();

			if(Test_Passing)
			{
				Test_Reporter->CasePass(suiteName, caseName);
			}
			else
			{
				++failures;
			}
		}
		catch(const NullUnit::Exception& e)
		{
			Test_Reporter->CaseAssertionFail(suiteName, caseName,
				e.Reason, e.Filename, e.LineNumber);
			++failures;
		}
		catch(const std::exception& e)
		{
			Test_Reporter->CaseStdExceptionFail(suiteName, caseName, e.what(),
				factory->Filename, factory->LineNumber);
			++failures;
		}
		catch(...)
		{
			Test_Reporter->CaseUnhandledExceptionFail(suiteName, caseName,
				factory->Filename, factory->LineNumber);
			++failures;
		}

		// Teardown case
		try
		{
			testCase->Teardown();
			testCase = nullptr;
		}
		catch(...)
		{
			Test_Reporter->FixtureTeardownFail(suiteName, caseName,
				factory->Filename, factory->LineNumber);
			++failures;
			return;
		}
	}

	void RunSuite(int& failures, const std::string& suiteName, std::shared_ptr<SuiteFactory> factory)
	{
		std::shared_ptr<Suite> suite = factory->CreateSuite();
		CaseVector& caseFactories = suite->GetCaseFactories();

		for(auto jt = caseFactories.begin(); jt != caseFactories.end(); ++jt)
		{
			Test_Reporter->CaseBegin(suiteName, jt->first);
			RunCase(failures, suiteName, jt->first, jt->second);
			Test_Reporter->CaseEnd(suiteName, jt->first);
		}
	}

	void RunOnlySuite(int& failures, const std::string& suiteName, const std::string& caseName, std::shared_ptr<SuiteFactory> factory)
	{
		auto suite = factory->CreateSuite();
		auto caseFac = suite->GetCaseFactoryMap().find(caseName);

		if(caseFac == suite->GetCaseFactoryMap().end())
		{
			++failures;
			std::cerr << Strings::MakeInvalidCaseNameString(suiteName, caseName) << std::endl;
		}
		else
		{
			Test_Reporter->CaseBegin(suiteName, caseFac->first);
			RunCase(failures, suiteName, caseFac->first, caseFac->second);
			Test_Reporter->CaseEnd(suiteName, caseFac->first);
		}
	}

	void RunCases(int& failures)
	{
		Test_Reporter->ReportBegin();

		SuiteMap& factories = SuiteRegistry::Get().Factories;
		for(auto it = factories.begin(); it != factories.end(); ++it)
		{
			Test_Reporter->SuiteBegin(it->first);
			RunSuite(failures, it->first, it->second);
			Test_Reporter->SuiteEnd(it->first);
		}

		Test_Reporter->ReportEnd();
	}

	void RunOnlyCases(int& failures, const std::vector<std::pair<std::string, std::string>>& cases)
	{
		Test_Reporter->ReportBegin();

		for(auto it = cases.begin(); it != cases.end(); ++it)
		{
			auto suiteFac = SuiteRegistry::Get().Factories.find(it->first);

			if(suiteFac == SuiteRegistry::Get().Factories.end())
			{
				++failures;
				std::cerr << Strings::MakeInvalidSuiteNameString(it->first) << std::endl;
			}
			else
			{
				if(it->second.empty())
				{
					RunSuite(failures, suiteFac->first, suiteFac->second);
				}
				else
				{
					RunOnlySuite(failures, suiteFac->first, it->second, suiteFac->second);
				}
			}
		}

		Test_Reporter->ReportEnd();
	}

	void ParseCaseName(const std::string& arg, std::pair<std::string, std::string>& pair)
	{
		auto it = arg.begin();
		
		for( ; it != arg.end(); ++it)
		{
			if(*it != '.')
			{
				pair.first.push_back(*it);
			}
			else
			{
				++it;
				break;
			}
		}

		for( ; it != arg.end(); ++it)
		{
			pair.second.push_back(*it);
		}
	}
}

int main(int argc, char** argv)
{
	bool runOnly = false;
	bool listOnly = false;
	NullUnit::ReporterType::Enum reporterType = NullUnit::ReporterType::Stream;
	std::vector<std::pair<std::string, std::string>> runOnlyCases;

	// Parse command line parameters
	for(int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);

		if(arg == "--list")
		{
			listOnly = true;
		}
		else if(arg == "--gui")
		{
			if(reporterType != NullUnit::ReporterType::Stream)
			{
				std::cerr << NullUnit::Strings::MultipleOutputTypes << std::endl;
				return 1;
			}
			else
			{
				reporterType = NullUnit::ReporterType::Gui;
			}
		}
		else if(arg == "--xml")
		{
			if(reporterType != NullUnit::ReporterType::Stream)
			{
				std::cerr << NullUnit::Strings::MultipleOutputTypes << std::endl;
				return 1;
			}
			else
			{
				reporterType = NullUnit::ReporterType::Xml;
			}
		}
		else if(arg == "--run")
		{
			runOnly = true;
			++i;

			for( ; i < argc; ++i)
			{
				std::pair<std::string, std::string> parsed_arg;

				NullUnit::ParseCaseName(argv[i], parsed_arg);

				runOnlyCases.push_back(parsed_arg);
			}
		}
		else
		{
			std::cerr << NullUnit::Strings::MakeIllegalArgumentString(arg) << std::endl;
			return 1;
		}
	}

	// Build reporter
	switch(reporterType)
	{
	default:
	case NullUnit::ReporterType::Stream:
		NullUnit::Test_Reporter = std::make_shared<NullUnit::StreamReporter>(std::cout);
		break;

	case NullUnit::ReporterType::Gui:
		NullUnit::Test_Reporter = std::make_shared<NullUnit::GuiReporter>(std::cout);
		break;

	case NullUnit::ReporterType::Xml:
		NullUnit::Test_Reporter = std::make_shared<NullUnit::XmlReporter>(std::cout);
		break;
	}

	int failures = 0;

	try
	{
		if(listOnly)
		{
			if(runOnly)
			{
				NullUnit::ListOnlyCases(failures, runOnlyCases);
			}
			else
			{
				NullUnit::ListCases();
			}
		}
		else
		{
			if(runOnly)
			{
				NullUnit::RunOnlyCases(failures, runOnlyCases);
			}
			else
			{
				NullUnit::RunCases(failures);
			}
		}
	}
	catch(const NullUnit::InternalException& e)
	{
		std::cerr << e.Reason << std::endl;
		return 1;
	}

	return (failures == 0) ? 0 : 1;
}
