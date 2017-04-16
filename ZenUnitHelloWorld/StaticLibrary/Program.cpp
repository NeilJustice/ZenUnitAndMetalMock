#include "pch.h"
#include "Program.h"
#include "Console.h"
#include "ArgsParser.h"

Program::Program()
   : _console(new Console)
   , _argsParser(new ArgsParser)
{
}

int Program::Main(int argc, char* argv[]) const
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
   return VectorMain(args);
}

int Program::VectorMain(const std::vector<std::string>& args) const
{
   int exitCode = 0;
   try
   {
      ProgramArgs programArgs = _argsParser->Parse(args);
      exitCode = ArgsMain(programArgs);
   }
   catch (const std::exception& e)
   {
      _console->WriteLine(e.what());
      exitCode = 1;
   }
   return exitCode;
}

int Program::ArgsMain(const ProgramArgs&) const
{
   return 0;
}

Program::~Program()
{
}
