#include "pch.h"
#include "Program.h"
#include "Console.h"

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

const string Program::CommandLineUsage = R"(ProgramName v0.1.0)";

int Program::VectorMain(const vector<string>& args) const
{
   assert(args.size() >= 1);
   return 0;
}

Program::~Program()
{
}
