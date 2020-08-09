#include "pch.h"
#include "ZenUnitTestUtils/UserType.h"

namespace MetalMock
{
   TESTS(UnexpectedCallExceptionTests)
   FACTS(OneArgumentConstructor_SetsWhatToExpectedMessage_ClassIsSubclassOfMetalMockException)
   AFACT(OneOrMoreArgumentsConstructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   AFACT(OneOrMoreArgumentsConstructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   EVIDENCE

   const string ExpectedUnexpectedCallPrefix = "Unexpected call to MetalMocked function:\n";
   const string VoidSignature0 = "void ClassName::FunctionName()";
   const string VirtualVoidSignature0 = "virtual void ClassName::FunctionName()";
   const string NonVoidASignature0 = "virtual int ClassName::FunctionName()";
   const string NonVoidBSignature0 = "void_prefixed_type ClassName::FunctionName()";
   const string VoidSignature1 = "void ClassName::FunctionName(int)";
   const string VoidSignature2 = "void ClassName::FunctionName(int, int)";

   TEST1X1(OneArgumentConstructor_SetsWhatToExpectedMessage_ClassIsSubclassOfMetalMockException,
      const string& metalMockedFunctionSignature,
      VoidSignature0,
      VirtualVoidSignature0,
      NonVoidASignature0,
      NonVoidBSignature0)
   {
      const UnexpectedCallException ex(metalMockedFunctionSignature);
      //
      const string expectedWhat = ExpectedUnexpectedCallPrefix + metalMockedFunctionSignature;
      const char* const what = ex.what();
      ARE_EQUAL(expectedWhat, what);
      IS_TRUE((is_base_of<MetalMockException, UnexpectedCallException>::value));
   }

   TEST(OneOrMoreArgumentsConstructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   {
      const UserType Argument1(1);
      //
      const UnexpectedCallException ex(VoidSignature0, Argument1);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Argument1: UserType@1)";
      const char* const what = ex.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   TEST(OneOrMoreArgumentsConstructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   {
      const UserType Argument1(1);
      const UserType Argument2(2);
      //
      const UnexpectedCallException ex(VoidSignature0, Argument1, Argument2);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Argument1: UserType@1
Argument2: UserType@2)";
      const char* const what = ex.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   RUN_TESTS(UnexpectedCallExceptionTests)
}
