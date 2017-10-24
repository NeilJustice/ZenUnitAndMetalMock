#pragma once

namespace ZenUnit
{
   struct RunFilter
   {
      std::string testClassName;
      std::string testName;
      unsigned testCaseNumber = 0;
   };
}