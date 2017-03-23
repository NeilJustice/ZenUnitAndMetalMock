#pragma once

namespace ZenUnit
{
   class Set
   {
   public:
      template<typename SetType, typename T>
      static bool Contains(const SetType& s, const T& element)
      {
         bool setContainsElement = s.find(element) != s.end();
         return setContainsElement;
      }
   };
}
