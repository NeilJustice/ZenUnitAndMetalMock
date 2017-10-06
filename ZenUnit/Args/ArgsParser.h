#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Utils/Time/Watch.h"
#include <memory>

namespace ZenUnit
{
   class Console;
   class Watch;

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const Watch> _watch;
      std::function<unsigned(const std::string&)> call_String_ToUnsigned;
   public:
      ArgsParser();
      virtual ~ArgsParser() = default;
      virtual ZenUnitArgs Parse(const std::vector<std::string>& args) const;
      static const std::string& Usage();
   };
}
