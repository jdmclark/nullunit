// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#include "nullunit/internal/t_exception.h"

NullUnit::Exception::Exception(const std::string& filename, const int lineNumber, const std::string& reason)
	: Filename(filename), Reason(reason), LineNumber(lineNumber)
{
	return;
}

NullUnit::InternalException::InternalException(const std::string& reason)
	: Reason(reason)
{
	return;
}
