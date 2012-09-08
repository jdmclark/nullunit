// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_CASEFAC_H_INCLUDED_
#define _T_CASEFAC_H_INCLUDED_

namespace NullUnit
{
	class CaseFactory
	{
	public:
		const std::string Filename;
		const int LineNumber;

		CaseFactory(const std::string& f, int ln)
			: Filename(f), LineNumber(ln)
		{
			return;
		}

		virtual ~CaseFactory()
		{
			return;
		}

		virtual Case* CreateCase() = 0;
	};

	template <typename T> class SpecifiedCaseFactory : public CaseFactory
	{
	public:
		SpecifiedCaseFactory(const std::string& f, int ln)
			: CaseFactory(f, ln)
		{
			return;
		}

		Case* CreateCase()
		{
			return new T();
		}
	};
}

#endif // _T_CASEFAC_H_INCLUDED_
