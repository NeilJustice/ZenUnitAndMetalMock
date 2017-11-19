#include "pch.h"
#include "Program.h"
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
   const int exitCode = VectorMain(args);
   return exitCode;
}

const std::string Program::CommandLineUsage = R"(ProgramName 0.1.0
Usage: ProgramName <FilePath> [-flag])";

int Program::VectorMain(const std::vector<std::string>& args) const
{
   assert(args.size() >= 1);
   if (args.size() == 1)
   {
      _console->WriteLine(CommandLineUsage);
      return 0;
   }
   try
   {
      _argsParser->ParseArgs(args);
      return 0;
   }
   catch (const std::exception& e)
   {
      _console->WriteLine(e.what());
      _console->WriteNewline();
      _console->WriteLine(CommandLineUsage);
      return 1;
   }
}

int Program::ArgsMain(const ProgramArgs&) const
{
   return 0;
}

Program::~Program()
{
}
