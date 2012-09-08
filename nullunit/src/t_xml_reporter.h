// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_XML_REPORTER_H_INCLUDED_
#define _T_XML_REPORTER_H_INCLUDED_

#include "nullunit/internal/t_reporter.h"

#include <string>
#include <memory>
#include <iostream>

namespace NullUnit
{
	namespace Xml
	{
		class XmlNode;

		class XmlList;
		class XmlListSuite;
		class XmlListCase;

		class XmlReport;
		class XmlReportSuite;
		class XmlReportCase;
		class XmlReportPass;
		class XmlReportFail;
	}

	class XmlReporter : public Reporter
	{
	private:
		std::ostream& stream;

		std::shared_ptr<Xml::XmlList> listRootNode;
		std::shared_ptr<Xml::XmlReport> reportRootNode;

		std::shared_ptr<Xml::XmlReportSuite> getReportSuite(const std::string&);
		std::shared_ptr<Xml::XmlReportCase> getReportCase(const std::string&, const std::string&);

		void addReportFail(const std::string& suite_name, const std::string& case_name,
			const std::string& reason, const std::string& filename, int lineNumber);

	public:
		XmlReporter(std::ostream& s);

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

#endif // _T_XML_REPORTER_H_INCLUDED_
