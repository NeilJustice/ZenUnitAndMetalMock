#pragma once

namespace ZenUnit
{
   template<>
   inline RunFilter Random<RunFilter>()
   {
      RunFilter randomRunFilter;
      randomRunFilter.testClassNamePattern = ZenUnit::Random<std::string>();
      randomRunFilter.testNamePattern = ZenUnit::Random<std::string>();
      randomRunFilter.testCaseNumber = ZenUnit::Random<size_t>();
      return randomRunFilter;
   }
}