#pragma once
#include <iostream>
#include <sstream>
#include <vector>

namespace ZenUnit
{
   class Vector
   {
   public:
      static std::vector<std::string> FromArgcArgv(int argc, char* argv[]);

      template<typename T>
      static std::string Join(const std::vector<T>& vec, char separator)
      {
         const size_t vectorSize = vec.size();
         if (vectorSize == 0)
         {
            return std::string();
         }
         std::ostringstream oss;
         for (size_t i = 0; i < vectorSize; ++i)
         {
            const T& element = vec[i];
            oss << element;
            if (i < vectorSize - 1)
            {
               oss << separator;
            }
         }
         const std::string joinedVectorString = oss.str();
         return joinedVectorString;
      }
   };
}
