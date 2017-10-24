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

   std::vector<RunFilter> RunFilterParser::Parse(const std::string& runArgument) const
   {
      std::vector<RunFilter> runFilters;
      std::vector<std::string> runArguments = String::Split(runArgument, ',');
      const RunFilter runFilter = FromString(runArguments[0]);
      runFilters.push_back(runFilter);
      return runFilters;
   }

   RunFilter RunFilterParser::FromString(const std::string& runArgument)
   {
      RunFilter runFilter;
      const std::string& runArgumentString = runArgument;
      const std::vector<std::string> testClassName_testNameSlashTestCaseNumber = String::Split(runArgumentString, '.');
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
