#include "pch.h"

struct DomainStruct
{
   int field1 = 0;
   std::string field2;
   std::vector<int> field3;
};

TESTS(DomainStructTests)
AFACT(EqualizerExampleTest)
EVIDENCE

TEST(EqualizerExampleTest)
{
   DomainStruct expectedDomainStruct;
   DomainStruct actualDomainStruct;
   ARE_EQUAL(expectedDomainStruct, actualDomainStruct);
}

RUN_TESTS(DomainStructTests)

namespace ZenUnit
{
   template<>
   struct Equalizer<DomainStruct>
   {
      static void AssertEqual(const DomainStruct& expectedDomainStruct, const DomainStruct& actualDomainStruct)
      {
         ARE_EQUAL(expectedDomainStruct.field1, actualDomainStruct.field1);
         ARE_EQUAL(expectedDomainStruct.field2, actualDomainStruct.field2);
         VECTORS_ARE_EQUAL(expectedDomainStruct.field3, actualDomainStruct.field3);
      }
   };
}

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
