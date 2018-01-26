#include "pch.h"
#include "StaticLibrary/Console.h"
#include "StaticLibrary/Program.h"

Program::Program()
   : _console(new Console)
{
}

int Program::Main(int argc, char* argv[]) const
{
   const vector<string> args = [&]()
   {
      vector<string> args;
      args.reserve(argc);
      for_each(argv, argv + argc, [&](char* arg)
      {
         args.emplace_back(arg);
      });
      return args;
   }();
   const int exitCode = VectorMain(args);
   return exitCode;
}

int Program::VectorMain(const vector<string>&) const
{
   _console->WriteLine("Hello World");
   return 0;
}

Program::~Program()
{
}
