#include "pch.h"
#include "RandomRunFilter.h"

RunFilter RandomRunFilter()
{
   RunFilter randomRunFilter;
   randomRunFilter.testClassName = ZenUnit::Random<std::string>();
   randomRunFilter.testName = ZenUnit::Random<std::string>();
   randomRunFilter.testCaseNumber = ZenUnit::Random<unsigned>();
   return randomRunFilter;
}