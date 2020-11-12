#include "pch.h"

//struct DomainStruct
//{
//   int field1 = 0;
//   std::string field2;
//   std::vector<int> field3;
//};
//
//TESTS(Tests)
//AFACT(Test)
//EVIDENCE
//
//TEST(Test)
//{
//   DomainStruct expectedDomainStruct;
//   DomainStruct actualDomainStruct;
//   ARE_EQUAL(expectedDomainStruct, actualDomainStruct);
//}
//
//RUN_TESTS(Tests)
//
//int main()
//{
//}

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
