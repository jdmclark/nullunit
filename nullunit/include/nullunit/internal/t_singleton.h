// Copyright (c) 2011-2012, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_SINGLETON_H_INCLUDED_
#define _T_SINGLETON_H_INCLUDED_

#include "nullunit/internal/t_uncopyable.h"

namespace NullUnit
{
	template <class T> class Singleton : Uncopyable
	{
	private:
		static T& instance;

	public:
		static T& Get()
		{
			static T t;
			return t;
		}
	};

	template <class T> T& Singleton<T>::instance = Get();
}

#endif // _T_SINGLETON_H_INCLUDED_
