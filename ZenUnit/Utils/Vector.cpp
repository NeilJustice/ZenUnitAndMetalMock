#include "pch.h"
#include "Vector.h"

namespace ZenUnit
{
   vector<string> Vector::FromArgcArgv(int argc, const char* argv[])
   {
      vector<string> args;
      const size_t argcSizeT = static_cast<size_t>(argc);
      args.resize(argcSizeT);
      for (size_t i = 0; i < argcSizeT; ++i)
      {
         const char* const ithArg = argv[i];
         args[i].assign(ithArg);
      }
      return args;
   }
}
