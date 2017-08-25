#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"

namespace ZenMock
{
   TESTS(UnexpectedCallExceptionTests)
   FACTS(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException)
   FACTS(Constructor_NonVoid0Args_SetsWhatToAlsoIncludeExpectAndReturnValue)
   FACT(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   FACT(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   EVIDENCE

   const string ExpectedUnexpectedCallPrefix = "Unexpected call to ZenMocked function\n\"";
   const string VoidSignature0 = "void ClassName::FunctionName()";
   const string VirtualVoidSignature0 = "virtual void ClassName::FunctionName()";
   const string NonVoidASignature0 = "virtual int ClassName::FunctionName()";
   const string NonVoidBSignature0 = "void_prefixed_type ClassName::FunctionName()";
   const string VoidSignature1 = "void ClassName::FunctionName(int)";
   const string VoidSignature2 = "void ClassName::FunctionName(int, int)";
   const string ExpectedFixForThisPrefix = R"(Fix for ZenMock::UnexpectedCallException:
Add before the unexpected call a call to [ZenMockedFunctionName]Mock.[Expect|)";
   const string ExpectedVoidFixForThisSuffix =
      "ExpectAndThrow<T>]()";
   const string ExpectedNonVoidFixForThisSuffix =
      "ExpectAndReturn|ExpectAndReturnValues|ExpectAndThrow<T>]()";

   TEST1X1(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException,
      const string& zenMockedFunctionSignature,
      VoidSignature0,
      VirtualVoidSignature0)
   {
      const UnexpectedCallException e(zenMockedFunctionSignature);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + zenMockedFunctionSignature + R"("
)" + ExpectedFixForThisPrefix + ExpectedVoidFixForThisSuffix;
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
      IS_TRUE((is_base_of<ZenMockException, UnexpectedCallException>::value));
   }

   TEST1X1(Constructor_NonVoid0Args_SetsWhatToAlsoIncludeExpectAndReturnValue,
      const string& zenMockedFunctionSignature,
      NonVoidASignature0,
      NonVoidBSignature0)
   {
      const UnexpectedCallException e(zenMockedFunctionSignature);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + zenMockedFunctionSignature + R"("
)" + ExpectedFixForThisPrefix + ExpectedNonVoidFixForThisSuffix;
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   TEST(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   {
      const UserType Arg1(1);
      //
      const UnexpectedCallException e(VoidSignature0, Arg1);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"("
Arg1: UserType@1
)" + ExpectedFixForThisPrefix + ExpectedVoidFixForThisSuffix;
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   TEST(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   {
      const UserType Arg1(1);
      const UserType Arg2(2);
      //
      const UnexpectedCallException e(VoidSignature0, Arg1, Arg2);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"("
Arg1: UserType@1
Arg2: UserType@2
)" + ExpectedFixForThisPrefix + ExpectedVoidFixForThisSuffix;
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   }; RUNTESTS(UnexpectedCallExceptionTests)
}
