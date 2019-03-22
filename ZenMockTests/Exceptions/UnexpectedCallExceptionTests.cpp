#include "pch.h"
#include "Testing/UserType.h"

namespace ZenMock
{
   TESTS(UnexpectedCallExceptionTests)
   FACTS(Constructor_SetsWhatToExpected_ClassIsSubclassOfZenMockException)
   AFACT(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   AFACT(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   EVIDENCE

   const string ExpectedUnexpectedCallPrefix = "Unexpected call to ZenMocked function:\n";
   const string VoidSignature0 = "void ClassName::FunctionName()";
   const string VirtualVoidSignature0 = "virtual void ClassName::FunctionName()";
   const string NonVoidASignature0 = "virtual int ClassName::FunctionName()";
   const string NonVoidBSignature0 = "void_prefixed_type ClassName::FunctionName()";
   const string VoidSignature1 = "void ClassName::FunctionName(int)";
   const string VoidSignature2 = "void ClassName::FunctionName(int, int)";

   TEST1X1(Constructor_SetsWhatToExpected_ClassIsSubclassOfZenMockException,
      const string& zenMockedFunctionSignature,
      VoidSignature0,
      VirtualVoidSignature0,
      NonVoidASignature0,
      NonVoidBSignature0)
   {
      const UnexpectedCallException e(zenMockedFunctionSignature);
      //
      const string expectedWhat = ExpectedUnexpectedCallPrefix + zenMockedFunctionSignature;
      const char* const what = e.what();
      ARE_EQUAL(expectedWhat, what);
      IS_TRUE((is_base_of<ZenMockException, UnexpectedCallException>::value));
   }

   TEST(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   {
      const UserType Argument1(1);
      //
      const UnexpectedCallException e(VoidSignature0, Argument1);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Argument1: UserType@1)";
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   TEST(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   {
      const UserType Argument1(1);
      const UserType Argument2(2);
      //
      const UnexpectedCallException e(VoidSignature0, Argument1, Argument2);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Argument1: UserType@1
Argument2: UserType@2)";
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   RUN_TESTS(UnexpectedCallExceptionTests)
}
