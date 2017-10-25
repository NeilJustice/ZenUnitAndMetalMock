#include "pch.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenUnit
{
   RunFilterParser::RunFilterParser()
      : _transformer(new Transformer<std::string, RunFilter>)
   {
   }

   RunFilterParser::~RunFilterParser() = default;

   std::vector<RunFilter> RunFilterParser::Parse(const std::vector<std::string>& runFilterStrings) const
   {
      std::vector<RunFilter> runFilters(runFilterStrings.size());
      _transformer->Transform(&runFilterStrings, runFilters, RunFilterParser::ParseRunFilterString);
      return runFilters;
   }

   RunFilter RunFilterParser::ParseRunFilterString(const std::string& runFilterString)
   {
      RunFilter runFilter;
      const std::vector<std::string> testClassName_testNameSlashTestCaseNumber = String::Split(runFilterString, '.');
      runFilter.testClassName = testClassName_testNameSlashTestCaseNumber[0];
      if (testClassName_testNameSlashTestCaseNumber.size() == 2)
      {
         const std::vector<std::string> testName_testCaseNumber = String::Split(testClassName_testNameSlashTestCaseNumber[1], '/');
         runFilter.testClassName = testClassName_testNameSlashTestCaseNumber[0];
         runFilter.testName = testName_testCaseNumber[0];
         if (testName_testCaseNumber.size() == 2)
         {
            runFilter.testCaseNumber = String::ToUnsigned(testName_testCaseNumber[1]);
         }
      }
      return runFilter;
   }
}
