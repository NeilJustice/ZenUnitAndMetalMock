#include "pch.h"
#include "StaticLibrary/Console.h"
#include "StaticLibrary/ProgramNameProgram.h"

ProgramNameProgram::ProgramNameProgram()
   : _console(new Console)
{
}

int ProgramNameProgram::Main(int argc, char* argv[]) const
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

int ProgramNameProgram::VectorMain(const vector<string>&) const
{
   _console->WriteLine("Hello World");
   return 0;
}

ProgramNameProgram::~ProgramNameProgram()
{
}
