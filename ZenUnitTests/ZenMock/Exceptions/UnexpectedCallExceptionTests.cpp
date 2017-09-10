#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"

namespace ZenMock
{
   TESTS(UnexpectedCallExceptionTests)
   FACTS(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException)
   FACTS(Constructor_NonVoid0Args_SetsWhatToAlsoIncludeExpectAndReturnValue)
   AFACT(Constructor_Void1Arg_SetsWhat_IncludesToStringedArg1)
   AFACT(Constructor_Void2Args_SetsWhat_IncludesToStringedArg1AndArg2)
   EVIDENCE

   const string ExpectedUnexpectedCallPrefix = "Unexpected call to ZenMocked function\n\"";
   const string VoidSignature0 = "void ClassName::FunctionName()";
   const string VirtualVoidSignature0 = "virtual void ClassName::FunctionName()";
   const string NonVoidASignature0 = "virtual int ClassName::FunctionName()";
   const string NonVoidBSignature0 = "void_prefixed_type ClassName::FunctionName()";
   const string VoidSignature1 = "void ClassName::FunctionName(int)";
   const string VoidSignature2 = "void ClassName::FunctionName(int, int)";
   const string ExpectedFixPrefix =
      R"(Fix: Add before the unexpected call a call to <ZenMockObjectName>.<FunctionName>Mock.[Expect|)";
   const string ExpectedVoidFixSuffix =
      "ExpectAndThrow<T>]()";
   const string ExpectedNonVoidFixSuffix =
      "ExpectAndReturn|ExpectAndReturnValues|ExpectAndThrow<T>]()";

   TEST1X1(Constructor_Void0Args_SetsWhatToJustExpectAndExpectAndThrow_ClassIsSubclassOfZenMockException,
      const string& zenMockedFunctionSignature,
      VoidSignature0,
      VirtualVoidSignature0)
   {
      const UnexpectedCallException e(zenMockedFunctionSignature);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + zenMockedFunctionSignature + R"("
)" + ExpectedFixPrefix + ExpectedVoidFixSuffix;
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
)" + ExpectedFixPrefix + ExpectedNonVoidFixSuffix;
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
)" + ExpectedFixPrefix + ExpectedVoidFixSuffix;
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
)" + ExpectedFixPrefix + ExpectedVoidFixSuffix;
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

   }; RUNTESTS(UnexpectedCallExceptionTests)
}
