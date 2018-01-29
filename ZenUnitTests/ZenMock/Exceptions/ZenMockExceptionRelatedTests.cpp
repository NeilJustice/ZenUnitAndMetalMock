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
   _exceptionThrower.Throw<runtime_error>("runtime_error_what");
   THROWS(_exceptionThrower.Throw<runtime_error>("runtime_error_what"), logic_error,
      "ExceptionThrower::Throw<T>() called twice");
}

TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
{
   _exceptionThrower.ZenMockThrowIfExceptionSet();
}

TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
{
   _exceptionThrower.Throw<runtime_error>("runtime_error_what");
   THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), runtime_error, "runtime_error_what");
}

TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
{
   _exceptionThrower.Throw<logic_error>("logic_error_what");
   THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), logic_error, "logic_error_what");
}

}; RUN_TESTS(ExceptionThrowerTests)


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
Already called [FunctionName]Mock.[Expect|Return|ReturnValues|Throw]().)";
   ARE_EQUAL(expectedWhat, e.what());
   IS_TRUE((is_base_of<ZenMockException, FunctionAlreadyExpectedException>::value));
}

}; RUN_TESTS(FunctionAlreadyExpectedExceptionTests)


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
[FunctionName]Mock.[Return|ReturnValues]())";
   ARE_EQUAL(ExpectedWhat, e.what());
   IS_TRUE((is_base_of<ZenMockException, ReturnValueMustBeSpecifiedException>::value));
}

}; RUN_TESTS(ReturnValueMustBeSpecifiedExceptionTests)


template<typename ExceptionType>
TEMPLATE_TESTS(TemplateThrowableTests, ExceptionType)
AFACT(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
AFACT(Throw_ExceptionIsNullptr_DoesNothing)
AFACT(Throw_ExceptionIsNotNullptr_ThrowsTheException)
EVIDENCE

TemplateThrowable<ExceptionType> _templateThrowable;
const string _exceptionWhat = ZenUnit::Random<string>();

TEST(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
{
   const Throwable* const throwable = TemplateThrowable<ExceptionType>::New(_exceptionWhat);
   THROWS(throwable->Throw(), ExceptionType, _exceptionWhat);
   delete throwable;
}

TEST(Throw_ExceptionIsNullptr_DoesNothing)
{
   _templateThrowable.Throw();
}

TEST(Throw_ExceptionIsNotNullptr_ThrowsTheException)
{
   _templateThrowable._exception = make_unique<ExceptionType>(_exceptionWhat);
   THROWS(_templateThrowable.Throw(), ExceptionType, _exceptionWhat);
}

};
RUN_TEMPLATE_TESTS(TemplateThrowableTests, runtime_error)
RUN_TEMPLATE_TESTS(TemplateThrowableTests, logic_error)


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

}; RUN_TESTS(UnexpectedCallExceptionTests)


TESTS(UnsupportedCalledZeroTimesExceptionTests)
AFACT(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
EVIDENCE

TEST(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
{
   // Example ZenMocked function signature: "virtual void ClassName::FunctionName(int, int) const"
   const string zenMockedFunctionSignature = ZenUnit::Random<string>();
   //
   const UnsupportedCalledZeroTimesException ex(zenMockedFunctionSignature);
   //
   const string ExpectedWhat = ZenUnit::String::Concat(
      "For ZenMocked function \"", zenMockedFunctionSignature, R"(":
ZenMock objects by design do not support asserting that
their corresponding ZenMocked functions were called zero times.
To assert that a ZenMocked function was called zero times,
simply do not call Expect(), Return(), or Throw() on a ZenMock object.)");
   const string actualWhat = ex.what();
   ARE_EQUAL(ExpectedWhat, actualWhat);
   IS_TRUE((is_base_of<ZenMockException, UnsupportedCalledZeroTimesException>::value));
}

}; RUN_TESTS(UnsupportedCalledZeroTimesExceptionTests)

}
