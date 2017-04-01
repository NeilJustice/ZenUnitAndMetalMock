#pragma once

namespace ZenUnit
{
   // For a given pointer to member function, PmfToken provides a unique const PmfToken* value
   // by way of a static variable inside of a pmf-specific template instanitation.
   // const PmfToken* is used in TestClassMacros.h: std::unordered_map<
   //    const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> s_testNXNPmfTokenToTest;
   struct PmfToken
   {
      PmfToken() = default;

      template<typename PmfType, PmfType>
      static const PmfToken* Instantiate()
      {
         const static PmfToken pmfToken;
         return &pmfToken;
      }
   };
}

#define PMFTOKEN(pmf) ZenUnit::PmfToken::Instantiate<decltype(pmf), pmf>()
