#include "pch.h"
#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(SetZenUnitPrinterTests, T)
   AFACT(Print_Set_PrintsStringRepresentationOfTheSet)
   AFACT(Print_UnorderedSet_PrintsStringRepresentationOfTheUnorderedSet)
   EVIDENCE

   TEST(Print_Set_PrintsStringRepresentationOfTheSet)
   {
      ostringstream oss;

      const string expectedTypeNameOfT = *Type::GetName<T>();

      ZenUnit::Printer<set<T>>::Print(oss, {});
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<T>>::Print(oss, { 1 });
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
   1
})", oss.str());
      oss = ostringstream();

#ifdef __linux__
      ZenUnit::Printer<set<T>>::Print(oss, { 1, 2 });
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
   2,
   1
})", oss.str());
      oss = ostringstream();
#elif _WIN32
      ZenUnit::Printer<set<T>>::Print(oss, { 1, 2 });
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
   1,
   2
})", oss.str());
      oss = ostringstream();
#endif

      ZenUnit::Printer<set<T>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
   1,
   2,
   3
})", oss.str());
      oss = ostringstream();


      // Does-compile confirmation
      ZenUnit::Printer<set<T, CustomLessComparator<T>>>::Print(oss, {});
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      ZenUnit::Printer<set<T, CustomLessComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("std::set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
   }

   TEST(Print_UnorderedSet_PrintsStringRepresentationOfTheUnorderedSet)
   {
      ostringstream oss;

      const string expectedTypeNameOfT = *Type::GetName<T>();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, {});
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1 });
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
   1
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1, 2 });
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
   1,
   2
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<T>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
   1,
   2,
   3
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      ZenUnit::Printer<unordered_set<T, CustomHasher<T>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      ZenUnit::Printer<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
      oss = ostringstream();

      // Does-compile confirmation
      ZenUnit::Printer<unordered_set<T, CustomHasher<T>, CustomEqualityComparator<T>, CustomAllocator<T>>>::Print(oss, {});
      ARE_EQUAL("std::unordered_set<" + expectedTypeNameOfT + R"(>
{
})", oss.str());
   }

   RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, int)
   THEN_RUN_TEMPLATE_TESTS(SetZenUnitPrinterTests, unsigned long long)


   TESTS(UserTypeSetZenUnitPrinterTests)
   AFACT(Print_Set_PrintsStringRepresentationOfTheSet)
   AFACT(Print_UnorderedSet_PrintsStringRepresentationOfTheUnorderedSet)
   EVIDENCE

   TEST(Print_Set_PrintsStringRepresentationOfTheSet)
   {
      ostringstream oss;

      ZenUnit::Printer<set<UserType>>::Print(oss, {});
      ARE_EQUAL(R"(std::set<UserType>
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<UserType>>::Print(oss, { 1 });
      ARE_EQUAL(R"(std::set<UserType>
{
   UserType@1
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<UserType>>::Print(oss, { 1, 2 });
      ARE_EQUAL(R"(std::set<UserType>
{
   UserType@1,
   UserType@2
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<set<UserType>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL(R"(std::set<UserType>
{
   UserType@1,
   UserType@2,
   UserType@3
})", oss.str());
   }

   TEST(Print_UnorderedSet_PrintsStringRepresentationOfTheUnorderedSet)
   {
      ostringstream oss;

      ZenUnit::Printer<unordered_set<UserType>>::Print(oss, {});
      ARE_EQUAL(R"(std::unordered_set<UserType>
{
})", oss.str());
      oss = ostringstream();

      ZenUnit::Printer<unordered_set<UserType>>::Print(oss, { 1 });
      ARE_EQUAL(R"(std::unordered_set<UserType>
{
   UserType@1
})", oss.str());
      oss = ostringstream();

#ifdef __linux__
      ZenUnit::Printer<unordered_set<UserType>>::Print(oss, { 1, 2 });
      ARE_EQUAL(R"(std::unordered_set<UserType>
{
   UserType@2,
   UserType@1
})", oss.str());
      oss = ostringstream();
#elif _WIN32
      ZenUnit::Printer<unordered_set<UserType>>::Print(oss, { 1, 2 });
      ARE_EQUAL(R"(std::unordered_set<UserType>
{
   UserType@1,
   UserType@2
})", oss.str());
      oss = ostringstream();
#endif

      ZenUnit::Printer<unordered_set<UserType>>::Print(oss, { 1, 2, 3 });
      ARE_EQUAL(R"(std::unordered_set<UserType>
{
   UserType@1,
   UserType@2,
   UserType@3
})", oss.str());
   }

   RUN_TESTS(UserTypeSetZenUnitPrinterTests)
}
