#pragma once
#include "ZenUnitArgs.h"
#include <memory>

namespace ZenUnit
{
   class Console;

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      std::unique_ptr<const Console> _console;
      std::function<unsigned(const std::string&)> _String_ToUnsigned;
   public:
      ArgsParser();
      virtual ~ArgsParser() = default;
      virtual ZenUnitArgs Parse(const std::vector<std::string>& args) const;
      static const std::string Usage;
   };
}
