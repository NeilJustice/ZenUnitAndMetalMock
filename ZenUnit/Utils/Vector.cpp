#include "pch.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   INLINE std::vector<std::string> Vector::FromArgcArgv(int argc, char* argv[])
   {
      const std::vector<std::string> args = [&]()
      {
         std::vector<std::string> args;
         args.reserve(argc);
         std::for_each(argv, argv + argc, [&](char* arg)
         {
            args.emplace_back(arg);
         });
         return args;
      }();
      return args;
   }
}
