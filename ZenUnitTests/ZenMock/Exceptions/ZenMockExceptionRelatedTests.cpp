#include "pch.h"
#include "ZenUnitTests/Testing/UserType.h"

namespace ZenMock
{
   TESTS(ExceptionThrowerTests)
   AFACT(ExpectAndThrowCalledTwice_Throws)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   EVIDENCE

   ExceptionThrower _exceptionThrower;

   TEST(ExpectAndThrowCalledTwice_Throws)
   {
      _exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what"), logic_error,
         "ExceptionThrower::ExpectAndThrow<T>() called twice");
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      _exceptionThrower.ZenMockThrowIfExceptionSet();
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      _exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), runtime_error, "runtime_error_what");
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   {
      _exceptionThrower.ExpectAndThrow<logic_error>("logic_error_what");
      THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), logic_error, "logic_error_what");
   }

   }; RUNTESTS(ExceptionThrowerTests)
}

namespace ZenMock
{
   TESTS(FunctionAlreadyExpectedExceptionTests)
   AFACT(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "void ClassName::FunctionName(int) const";
      //
      FunctionAlreadyExpectedException e(ZenMockedFunctionSignature);
      //
      const string expectedWhat = "For ZenMocked function \"" + ZenMockedFunctionSignature + R"(":
Already called [FunctionName]Mock.Expect[AndReturn|AndReturnValues|AndThrow]().)";
      ARE_EQUAL(expectedWhat, e.what());
      IS_TRUE((is_base_of<ZenMockException, FunctionAlreadyExpectedException>::value));
   }

}; RUNTESTS(FunctionAlreadyExpectedExceptionTests)
}


namespace ZenMock
{
   TESTS(ReturnValueMustBeSpecifiedExceptionTests)
      AFACT(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
      EVIDENCE

   TEST(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "ZenMockedFunctionSignature";
      //
      ReturnValueMustBeSpecifiedException e(ZenMockedFunctionSignature);
      //
      const string ExpectedWhat = R"(For ZenMocked function "ZenMockedFunctionSignature":
  ZenMocked functions with non-void return types
  must have their return value or values set explicitly by calling
  [FunctionName]Mock.[ExpectAndReturn|ExpectAndReturnValues]())";
      ARE_EQUAL(ExpectedWhat, e.what());
      IS_TRUE((is_base_of<ZenMockException, ReturnValueMustBeSpecifiedException>::value));
   }

}; RUNTESTS(ReturnValueMustBeSpecifiedExceptionTests)
}


namespace ZenMock
{
   template<typename ExceptionType>
   TEMPLATETESTS(TemplateThrowableTests, ExceptionType)
   AFACT(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   AFACT(Throw_ExceptionIsNullptr_DoesNothing)
   AFACT(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   EVIDENCE

   TemplateThrowable<ExceptionType> _templateThrowable;
   const string ExceptionWhat = "ExceptionWhat";

   TEST(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   {
      const Throwable* const throwable = TemplateThrowable<ExceptionType>::New(ExceptionWhat);
      THROWS(throwable->Throw(), ExceptionType, ExceptionWhat);
      delete throwable;
   }

   TEST(Throw_ExceptionIsNullptr_DoesNothing)
   {
      _templateThrowable.Throw();
   }

   TEST(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   {
      _templateThrowable._exception = make_unique<ExceptionType>(ExceptionWhat);
      THROWS(_templateThrowable.Throw(), ExceptionType, ExceptionWhat);
   }

};
RUNTEMPLATETESTS(TemplateThrowableTests, runtime_error)
RUNTEMPLATETESTS(TemplateThrowableTests, logic_error)
}


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
      const UserType Arg1(1);
      //
      const UnexpectedCallException e(VoidSignature0, Arg1);
      //
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Arg1: UserType@1)";
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
      const string ExpectedWhat = ExpectedUnexpectedCallPrefix + VoidSignature0 + R"(
Arg1: UserType@1
Arg2: UserType@2)";
      const char* const what = e.what();
      ARE_EQUAL(ExpectedWhat, what);
   }

}; RUNTESTS(UnexpectedCallExceptionTests)
}


namespace ZenMock
{
   TESTS(UnsupportedCalledZeroTimesExceptionTests)
   AFACT(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName(int, int) const";
      //
      const UnsupportedCalledZeroTimesException e(ZenMockedFunctionSignature);
      //
      const string ExpectedWhat = ZenUnit::String::Concat(
         "For ZenMocked function \"", ZenMockedFunctionSignature, R"(":
 ZenMock objects by design do not support the operation of asserting that
 their corresponding ZenMocked function was called zero times.
 To confirm that a ZenMocked function was called zero times,
 simply do not call any of the Expect() functions on a ZenMock object.)");
      const string actualWhat = e.what();
      ARE_EQUAL(ExpectedWhat, actualWhat);
      IS_TRUE((is_base_of<ZenMockException, UnsupportedCalledZeroTimesException>::value));
   }

}; RUNTESTS(UnsupportedCalledZeroTimesExceptionTests)
}
