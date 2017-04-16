#include "pch.h"
#include "ArgsParser.h"

ProgramArgs ArgsParser::Parse(const std::vector<std::string>& args) const
{
   ProgramArgs programArgs;
   for (const std::string& arg : args)
   {
      if (arg == "-flagA")
      {
         programArgs.flagA = true;
      }
      else if (arg == "-flagB")
      {
         programArgs.flagB = true;
      }
   }
   return programArgs;
}

ArgsParser::~ArgsParser()
{
}
