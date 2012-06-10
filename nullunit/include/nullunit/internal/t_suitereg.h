// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_SUITEREG_H_INCLUDED_
#define _T_SUITEREG_H_INCLUDED_

namespace NullUnit
{
	class SuiteFactory;

	typedef std::unordered_map<std::string, std::shared_ptr<SuiteFactory>> SuiteMap;
	class SuiteRegistry : public Singleton<SuiteRegistry>
	{
		friend class Singleton<SuiteRegistry>;

	private:
		SuiteRegistry()
		{
			return;
		}

	public:
		SuiteMap Factories;
	};

	template <typename T> void RegisterSuite(const std::string& s,
		const std::string& fileName, int lineNumber)
	{
		SuiteRegistry::Get().Factories.insert(
			std::make_pair(s, std::make_shared<SpecifiedSuiteFactory<T>>(
				fileName, lineNumber)));
		return;
	}
}

#endif // _T_SUITEREG_H_INCLUDED_
