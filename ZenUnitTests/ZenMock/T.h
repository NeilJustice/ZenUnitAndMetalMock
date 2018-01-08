#pragma once

namespace ZenMock
{
   template<size_t Value>
   struct T
   {
      bool flag;

      T() : flag(false) {}
      explicit T(bool flag) : flag(flag) {}

      friend bool operator==(const T<Value>& lhs, const T<Value>& rhs)
      {
         return lhs.flag == rhs.flag;
      }
   };
}
