#pragma once
#include <iostream>
#include <set>
#include <unordered_set>

namespace ZenUnit
{
   template<typename T, typename LessComparator, typename Allocator>
   struct Printer<std::set<T, LessComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::set<T, LessComparator, Allocator>&)
      {
         os << "SetType<T>";
      }
   };

   template<typename T, typename Hasher, typename EqualityComparator, typename Allocator>
   struct Printer<std::unordered_set<T, Hasher, EqualityComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::unordered_set<T, Hasher, EqualityComparator, Allocator>&)
      {
         os << "SetType<T>";
      }
   };
}
