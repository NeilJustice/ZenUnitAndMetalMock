#pragma once
#include <iostream>
#include <vector>

namespace ZenUnit
{
   template<typename T, typename Allocator>
   struct Printer<std::vector<T, Allocator>>
   {
      static void Print(std::ostream& os, const std::vector<T, Allocator>&)
      {
         os << "vector<T>";
      }
   };
}
