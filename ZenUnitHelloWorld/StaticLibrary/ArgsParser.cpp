#include "pch.h"
#include "ArgsParser.h"

ProgramArgs ArgsParser::ParseArgs(const std::vector<std::string>& args) const
{
   assert(args.size() >= 2);
   ProgramArgs programArgs;
   for (size_t i = 1; i < args.size(); ++i)
   {
      const std::string& arg = args[i];
      if (arg == "-flag")
      {
         programArgs.flag = true;
      }
      else
      {
         throw std::invalid_argument("Invalid argument: " + arg);
      }
   }
   return programArgs;
}

ArgsParser::~ArgsParser()
{
}
