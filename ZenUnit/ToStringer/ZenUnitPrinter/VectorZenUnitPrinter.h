#pragma once

template<typename T, typename Allocator>
struct ZenUnitPrinter<std::vector<T, Allocator>>
{
   static void Print(std::ostream& os, const std::vector<T, Allocator>&)
   {
      os << "vector<T>";
   }
};
