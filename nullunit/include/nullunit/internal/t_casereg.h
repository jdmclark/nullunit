// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

#ifndef _T_CASEREG_H_INCLUDED_
#define _T_CASEREG_H_INCLUDED_

namespace NullUnit
{
	typedef std::vector<std::pair<std::string, std::shared_ptr<CaseFactory>>> CaseVector;
	typedef std::unordered_map<std::string, std::shared_ptr<CaseFactory>> CaseMap;
	template <typename T> class CaseRegistry : public Singleton< CaseRegistry<T> >
	{
		friend class Singleton< CaseRegistry<T> >;

	private:
		CaseRegistry()
			: Locked(false)
		{
			return;
		}

	public:
		bool Locked;
		CaseVector Factories;
		CaseMap FactoryMap;
	};

	template <typename T, typename C> void RegisterCase(const std::string& s,
		const std::string& fileName, int lineNumber)
	{
		CaseRegistry<T>& reg = CaseRegistry<T>::Get();

		if(!reg.Locked)
		{
			auto pair = std::make_pair(s, std::make_shared<SpecifiedCaseFactory<C>>(fileName, lineNumber));

			reg.Factories.push_back(pair);
			reg.FactoryMap.insert(pair);
		}

		return;
	}

	template <typename T> void LockCaseRegistry()
	{
		CaseRegistry<T>::Get().Locked = true;
	}
}

#endif // _T_CASEREG_H_INCLUDED_
