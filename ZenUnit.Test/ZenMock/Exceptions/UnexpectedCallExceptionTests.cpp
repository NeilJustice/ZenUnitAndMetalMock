#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"

namespace ZenMock
{
   TESTS(UnexpectedCallExceptionTests)
   SPECX(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException)
   SPECX(Constructor_NonVoid0Args_SetsWhatToAlsoIncludeExpectAndReturnValue)
   SPEC(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   SPEC(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   SPECEND

   const string ExpectedUnexpectedCallPrefix = "Unexpected call to \"";
   const string VoidSignature0 = "void ClassName::FunctionName()";
   const string VirtualVoidSignature0 = "virtual void ClassName::FunctionName()";
   const string NonVoidASignature0 = "virtual int ClassName::FunctionName()";
   const string NonVoidBSignature0 = "void_prefixed_type ClassName::FunctionName()";
   const string VoidSignature1 = "void ClassName::FunctionName(int)";
   const string VoidSignature2 = "void ClassName::FunctionName(int, int)";
   const string ExpectedFixForThisPrefix = R"(Fix for this: Add before the unexpected call a call to
[ZenMockObjectName].[Expect or )";
   const string ExpectedVoidFixForThisSuffix =
      "ExpectAndThrow]()";
   const string ExpectedNonVoidFixForThisSuffix =
      "ExpectAndReturn or ExpectAndReturnValues or ExpectAndThrow]()";

   TEST1X1(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException,
      string zenMockedFunctionSignature,
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
      string zenMockedFunctionSignature,
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

   }; RUN(UnexpectedCallExceptionTests)
}
