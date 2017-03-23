#pragma once
#include <memory>
#include "ZenUnitArgs.h"

namespace ZenUnit
{
   class Console;

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      std::unique_ptr<const Console> _console;
   public:
      ArgsParser();
      virtual ~ArgsParser() {}
      virtual ZenUnitArgs Parse(const std::vector<std::string>& args) const;
      static const std::string Usage;
   };
}
