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

   std::vector<RunFilter> RunFilterParser::Parse(const std::vector<std::string>& testRunFilters) const
   {
      std::vector<RunFilter> runFilters = _transformer->Transform(
         &testRunFilters, RunFilterParser::ParseRunFilterString);
      return runFilters;
   }

   RunFilter RunFilterParser::ParseRunFilterString(const std::string& testRunFilter)
   {
      RunFilter runFilter;
      const std::vector<std::string> testClassName_testNameSlashTestCaseNumber = String::Split(testRunFilter, '.');
      if (testClassName_testNameSlashTestCaseNumber.size() > 2)
      {
         throw std::invalid_argument("Invalid test run filter: " + testRunFilter);
      }
      runFilter.testClassName = testClassName_testNameSlashTestCaseNumber[0];
      if (testClassName_testNameSlashTestCaseNumber.size() == 2)
      {
         const std::vector<std::string> testName_testCaseNumber
            = String::Split(testClassName_testNameSlashTestCaseNumber[1], '/');
         if (testName_testCaseNumber.size() > 2)
         {
            throw std::invalid_argument("Invalid test run filter: " + testRunFilter);
         }
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
