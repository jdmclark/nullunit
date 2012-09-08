// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_SUITEFAC_H_INCLUDED_
#define _T_SUITEFAC_H_INCLUDED_

#include "nullunit/internal/t_suite.h"
#include "nullunit/internal/t_reporter.h"

#include <memory>
#include <string>

#include <iostream>

namespace NullUnit
{
	class SuiteFactory
	{
	public:
		const std::string Filename;
		const int LineNumber;

		SuiteFactory(const std::string& f, int ln)
			: Filename(f), LineNumber(ln)
		{
			return;
		}

		virtual ~SuiteFactory()
		{
			return;
		}

		virtual std::shared_ptr<Suite> CreateSuite() = 0;
	};

	template <typename T> class SpecifiedSuiteFactory : public SuiteFactory
	{
	public:
		SpecifiedSuiteFactory(const std::string& f, int ln)
			: SuiteFactory(f, ln)
		{
			return;
		}

		std::shared_ptr<Suite> CreateSuite()
		{
			return std::make_shared<T>();
		}
	};
}

#endif // _T_SUITEFAC_H_INCLUDED_
