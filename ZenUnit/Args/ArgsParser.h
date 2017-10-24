#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include <memory>

namespace ZenUnit
{
   class Console;
   class RunFilterParser;

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const RunFilterParser> _runFilterParser;
      std::function<unsigned(const std::string&)> call_String_ToUnsigned;
   public:
      ArgsParser();
      virtual ~ArgsParser();
      virtual ZenUnitArgs Parse(const std::vector<std::string>& args) const;
      static const std::string& Usage();
   private:
      void WriteZenUnitArgumentErrorAndUsageThenExit1(const std::string& errorMessage) const;
   };
}
