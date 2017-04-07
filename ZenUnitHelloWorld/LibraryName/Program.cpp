#include "pch.h"
#include "Program.h"

int Program::Main(int argc, char* argv[]) const
{
   const vector<string> args = [&]()
   {
      vector<string> args;
      args.reserve(argc);
      for_each(argv, argv + argc, [&](char* arg) { args.emplace_back(arg); });
      return args;
   }();
   return Main(args);
}

int Program::Main(const vector<string>&) const
{
   cout << "Hello ZenUnit!\n";
   return 0;
}
