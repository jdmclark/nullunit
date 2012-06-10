// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_EXCEPTION_H_INCLUDED_
#define _T_EXCEPTION_H_INCLUDED_

#include <string>

namespace NullUnit
{
	class Exception
	{
	public:
		const std::string Filename, Reason;
		const int LineNumber;

		Exception(const std::string& filename, const int lineNumber, const std::string& reason);
	};

	class InternalException
	{
	public:
		const std::string Reason;

		InternalException(const std::string& reason);
	};
}

#endif // _T_EXCEPTION_H_INCLUDED_
