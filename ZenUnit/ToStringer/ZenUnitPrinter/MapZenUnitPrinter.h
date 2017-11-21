#pragma once
#include <iostream>
#include <map>
#include <unordered_map>

namespace ZenUnit
{
   template<typename TKey, typename TValue, typename LessComparator, typename Allocator>
   struct Printer<std::map<TKey, TValue, LessComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::map<TKey, TValue, LessComparator, Allocator>&)
      {
         os << "std::map<TKey, TValue>";
      }
   };

   template<typename TKey, typename TValue, typename Hasher, typename EqualityComparator, typename Allocator>
   struct Printer<std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>&)
      {
         os << "std::unordered_map<TKey, TValue>";
      }
   };
}
