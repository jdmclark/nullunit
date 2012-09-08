// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include "t_xml_reporter.h"
#include "t_strings.h"
#include "nullunit/internal/t_exception.h"

#include <unordered_map>
#include <vector>

namespace NullUnit
{
	namespace Xml
	{
		class XmlNodeVisitor
		{
		public:
			virtual void visitXmlList(XmlList&) = 0;
			virtual void visitXmlListSuite(XmlListSuite&) = 0;
			virtual void visitXmlListCase(XmlListCase&) = 0;
			virtual void visitXmlReport(XmlReport&) = 0;
			virtual void visitXmlReportSuite(XmlReportSuite&) = 0;
			virtual void visitXmlReportCase(XmlReportCase&) = 0;
			virtual void visitXmlReportPass(XmlReportPass&) = 0;
			virtual void visitXmlReportFail(XmlReportFail&) = 0;
		};

		class XmlNode
		{
		public:
			virtual void accept(XmlNodeVisitor&) = 0;
		};

		class XmlList : public XmlNode
		{
		public:
			std::unordered_map<std::string, std::shared_ptr<XmlListSuite>> suites;

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlList(*this);
			}
		};

		class XmlListSuite : public XmlNode
		{
		public:
			std::vector<std::shared_ptr<XmlListCase>> cases;

			const std::string name;
			const std::string filename;
			const int lineNumber;

			XmlListSuite(const std::string& n, const std::string& fn, int ln)
				: name(n), filename(fn), lineNumber(ln)
			{
				return;
			}

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlListSuite(*this);
			}
		};

		class XmlListCase : public XmlNode
		{
		public:
			const std::string name;
			const std::string filename;
			const int lineNumber;

			XmlListCase(const std::string& n, const std::string& fn, int ln)
				: name(n), filename(fn), lineNumber(ln)
			{
				return;
			}

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlListCase(*this);
			}
		};


		class XmlReport : public XmlNode
		{
		public:
			std::unordered_map<std::string, std::shared_ptr<XmlReportSuite>> suites;

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlReport(*this);
			}
		};

		class XmlReportSuite : public XmlNode
		{
		public:
			std::unordered_map<std::string, std::shared_ptr<XmlReportCase>> cases;

			const std::string name;

			XmlReportSuite(const std::string& n) : name(n)
			{
				return;
			}

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlReportSuite(*this);
			}
		};

		class XmlReportCase : public XmlNode
		{
		public:
			std::vector<std::shared_ptr<XmlNode>> results;

			const std::string name;

			XmlReportCase(const std::string& n) : name(n)
			{
				return;
			}

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlReportCase(*this);
			}
		};

		class XmlReportPass : public XmlNode
		{
		public:
			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlReportPass(*this);
			}
		};

		class XmlReportFail : public XmlNode
		{
		public:
			const std::string reason;
			const std::string filename;
			const int lineNumber;

			XmlReportFail(const std::string& r, const std::string& fn, int ln)
				: reason(r), filename(fn), lineNumber(ln)
			{
				return;
			}

			void accept(XmlNodeVisitor& v)
			{
				v.visitXmlReportFail(*this);
			}
		};

		class XmlReportStreamVisitor : public XmlNodeVisitor
		{
			std::ostream& stream;
			int tablevel;

			inline void printTabs()
			{
				for(int i = 0; i < tablevel; ++i)
				{
					stream << "\t";
				}
			}

		public:
			XmlReportStreamVisitor(std::ostream& os) : stream(os), tablevel(0)
			{
				return;
			}

			void visitXmlList(XmlList& n)
			{
				printTabs();
				stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;

				printTabs();
				stream << "<nu:list xmlns:nu=\"" << Strings::XmlListSchemaUri << "\">" << std::endl;

				++tablevel;
				for(auto it = n.suites.begin(); it != n.suites.end(); ++it)
				{
					it->second->accept(*this);
				}
				--tablevel;

				printTabs();
				stream << "</nu:list>" << std::endl;
			}

			void visitXmlListSuite(XmlListSuite& n)
			{
				printTabs();
				stream << "<nu:suite name=\"" << n.name << "\" filename=\"" << n.filename <<
					"\" line=\"" << n.lineNumber << "\">" << std::endl;

				++tablevel;
				for(auto it = n.cases.begin(); it != n.cases.end(); ++it)
				{
					(*it)->accept(*this);
				}
				--tablevel;

				printTabs();
				stream << "</nu:suite>" << std::endl;
			}

			void visitXmlListCase(XmlListCase& n)
			{
				printTabs();
				stream << "<nu:case name=\"" << n.name << "\" filename=\"" << n.filename <<
					"\" line=\"" << n.lineNumber << "\" />" << std::endl;
			}

			void visitXmlReport(XmlReport& n)
			{
				printTabs();
				stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;

				printTabs();
				stream << "<nu:report xmlns:nu=\"" << Strings::XmlReportSchemaUri << "\">" << std::endl;

				++tablevel;
				for(auto it = n.suites.begin(); it != n.suites.end(); ++it)
				{
					it->second->accept(*this);
				}
				--tablevel;

				printTabs();
				stream << "</nu:report>" << std::endl;
			}

			void visitXmlReportSuite(XmlReportSuite& n)
			{
				printTabs();
				stream << "<nu:suite name=\"" << n.name << "\">" << std::endl;

				++tablevel;
				for(auto it = n.cases.begin(); it != n.cases.end(); ++it)
				{
					it->second->accept(*this);
				}
				--tablevel;

				printTabs();
				stream << "</nu:suite>" << std::endl;
			}

			void visitXmlReportCase(XmlReportCase& n)
			{
				printTabs();
				stream << "<nu:case name=\"" << n.name << "\">" << std::endl;

				++tablevel;
				for(auto it = n.results.begin(); it != n.results.end(); ++it)
				{
					(*it)->accept(*this);
				}
				--tablevel;

				printTabs();
				stream << "</nu:case>" << std::endl;
			}

			void visitXmlReportPass(XmlReportPass&)
			{
				printTabs();
				stream << "<nu:pass />" << std::endl;
			}

			void visitXmlReportFail(XmlReportFail& n)
			{
				printTabs();
				stream << "<nu:fail filename=\"" << n.filename << "\" line=\"" << n.lineNumber << "\">" << std::endl;

				++tablevel;
				printTabs();
				stream << "<![CDATA[" << std::endl;
				++tablevel;
				printTabs();
				stream << n.reason << std::endl;
				--tablevel;
				printTabs();
				stream << "]]>" << std::endl;
				--tablevel;

				printTabs();
				stream << "</nu:fail>" << std::endl;
			}
		};
	}
}

NullUnit::XmlReporter::XmlReporter(std::ostream& s) : stream(s)
{
	listRootNode = std::make_shared<Xml::XmlList>();
	reportRootNode = std::make_shared<Xml::XmlReport>();
	return;
}

void NullUnit::XmlReporter::ListBegin()
{
}

void NullUnit::XmlReporter::ListEnd()
{
	// End of report. Print.
	Xml::XmlReportStreamVisitor v(stream);
	listRootNode->accept(v);
}

void NullUnit::XmlReporter::ListEntrySuite(const std::string& suite_name,
	const std::string& filename, int lineNumber)
{
	auto it = listRootNode->suites.find(suite_name);
	if(it == listRootNode->suites.end())
	{
		listRootNode->suites.insert(std::make_pair(suite_name,
			std::make_shared<Xml::XmlListSuite>(suite_name, filename, lineNumber)));
	}
}

void NullUnit::XmlReporter::ListEntryCase(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	auto it = listRootNode->suites.find(suite_name);
	if(it == listRootNode->suites.end())
	{
		throw InternalException(Strings::CaseBeforeSuite);
	}

	it->second->cases.push_back(std::make_shared<Xml::XmlListCase>(
		case_name, filename, lineNumber));
}

void NullUnit::XmlReporter::ReportBegin()
{
}

void NullUnit::XmlReporter::ReportEnd()
{
	// End of report. Print.
	Xml::XmlReportStreamVisitor v(stream);
	reportRootNode->accept(v);
}

std::shared_ptr<NullUnit::Xml::XmlReportSuite> NullUnit::XmlReporter::getReportSuite(const std::string& suite_name)
{
	auto it = reportRootNode->suites.find(suite_name);
	if(it == reportRootNode->suites.end())
	{
		std::shared_ptr<Xml::XmlReportSuite> p = std::make_shared<Xml::XmlReportSuite>(suite_name);
		reportRootNode->suites.insert(std::make_pair(suite_name, p));
		return p;
	}
	else
	{
		return it->second;
	}
}

std::shared_ptr<NullUnit::Xml::XmlReportCase> NullUnit::XmlReporter::getReportCase(
	const std::string& suite_name, const std::string& case_name)
{
	std::shared_ptr<Xml::XmlReportSuite> suite = getReportSuite(suite_name);

	auto it = suite->cases.find(case_name);
	if(it == suite->cases.end())
	{
		std::shared_ptr<Xml::XmlReportCase> p = std::make_shared<Xml::XmlReportCase>(case_name);
		suite->cases.insert(std::make_pair(case_name, p));
		return p;
	}
	else
	{
		return it->second;
	}
}

void NullUnit::XmlReporter::SuiteBegin(const std::string& suite_name)
{
	getReportSuite(suite_name);
}

void NullUnit::XmlReporter::SuiteEnd(const std::string& suite_end)
{
}

void NullUnit::XmlReporter::CaseBegin(const std::string& suite_name, const std::string& case_name)
{
	getReportCase(suite_name, case_name);
}

void NullUnit::XmlReporter::CaseEnd(const std::string& suite_name, const std::string& case_name)
{
}

void NullUnit::XmlReporter::CasePass(const std::string& suite_name, const std::string& case_name)
{
	auto p = getReportCase(suite_name, case_name);
	p->results.push_back(std::make_shared<Xml::XmlReportPass>());
}

void NullUnit::XmlReporter::addReportFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	auto p = getReportCase(suite_name, case_name);
	p->results.push_back(std::make_shared<Xml::XmlReportFail>(reason, filename, lineNumber));
}

void NullUnit::XmlReporter::CaseFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::XmlReporter::CaseStdExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& what, const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, Strings::MakeUnhandledStdExceptionString(what), filename, lineNumber);
}

void NullUnit::XmlReporter::CaseUnhandledExceptionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, Strings::UnhandledException, filename, lineNumber);
}

void NullUnit::XmlReporter::CaseAssertionFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::XmlReporter::CaseExpectationFail(const std::string& suite_name, const std::string& case_name,
	const std::string& reason, const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, reason, filename, lineNumber);
}

void NullUnit::XmlReporter::FixtureSetupFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, Strings::FixtureSetupFailure, filename, lineNumber);
}

void NullUnit::XmlReporter::FixtureTeardownFail(const std::string& suite_name, const std::string& case_name,
	const std::string& filename, int lineNumber)
{
	addReportFail(suite_name, case_name, Strings::FixtureTeardownFailure, filename, lineNumber);
}
