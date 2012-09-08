// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_AUTORUN_H_INCLUDED_
#define _T_AUTORUN_H_INCLUDED_

namespace NullUnit
{
	template <void(*fn)(const std::string&, const std::string&, int)> class Autorun
	{
	public:
		Autorun(const std::string& s, const std::string& f, int ln)
		{
			fn(s, f, ln);
			return;
		}
	};
}

#endif // _T_AUTORUN_H_INCLUDED_
