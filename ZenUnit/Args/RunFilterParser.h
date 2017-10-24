#pragma once
#include "ZenUnit/Args/RunFilter.h"

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   class Transformer;

   class RunFilterParser
   {
      friend class RunFilterParserTests;
   private:
      std::unique_ptr<Transformer<std::string, RunFilter>> _transformer;
   public:
      RunFilterParser();
      virtual ~RunFilterParser() = default;
      virtual std::vector<RunFilter> Parse(const std::string& runFilterStrings) const;
   private:
      static RunFilter FromString(const std::string& s);
   };
}