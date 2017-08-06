#pragma once
#include <memory>

namespace ZenUnit
{
   class Console;
   class Watch;
   struct ZenUnitArgs;
   class MultiTestClassRunner;
   class MachineNameGetter;

   class PreamblePrinter
   {
      friend class PreamblePrinterTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const Watch> _watch;
      std::unique_ptr<const MachineNameGetter> _machineNameGetter;
   public:
      PreamblePrinter();
      virtual ~PreamblePrinter();
      virtual void PrintOpeningThreeLines(
         const ZenUnitArgs& zenUnitArgs,
         const MultiTestClassRunner* multiTestClassRunner) const;
   private:
      virtual std::string MakeThirdLinePrefix(size_t numberOfTestClasses) const;
      virtual std::string MakeThirdLineSuffix(bool random, unsigned short randomseed) const;
   };
}
