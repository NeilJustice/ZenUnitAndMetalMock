#include "pch.h"

class ComponentA
{
public:
   virtual void VirtualVoid() {}
   virtual void VirtualVoidConstTwoArgs(int, int) const {}
   virtual int VirtualNonVoid() { return 0; }
   virtual int VirtualNonVoidConst() const { return 0; }
};

struct ComponentAMock : public Zen::Mock<ComponentA>
{
   ZENMOCK_VOID0(VirtualVoid)
   ZENMOCK_VOID2_CONST(VirtualVoidConstTwoArgs, int, int)
   ZENMOCK_NONVOID0(int, VirtualNonVoid)
   ZENMOCK_NONVOID0_CONST(int, VirtualNonVoidConst)
};

class ComponentB
{
public:
   void VoidFunction() {}
   void VoidFunctionConst() const {}
   int NonVoidFunction() { return 0; }
   int NonVoidFunctionConst() { return 0; }
};

struct ComponentBMock : public Zen::Mock<ComponentB>
{
   ZENMOCK_VOID0_NONVIRTUAL(VoidFunction)
   ZENMOCK_VOID0_CONST_NONVIRTUAL(ConstVoidFunction)
   ZENMOCK_NONVOID0_NONVIRTUAL(int, NonVoidFunction)
   ZENMOCK_NONVOID0_CONST_NONVIRTUAL(int, ConstNonVoidFunction)
};

class ClassUnderTest
{
   friend class ClassUnderTestTests;
private:
   std::unique_ptr<ComponentA> _componentA;
public:
   ClassUnderTest()
      : _componentA(new ComponentA)
   {
   }

   int InteractWithComponentA()
   {
      _componentA->VirtualVoid();
      _componentA->VirtualVoidConstTwoArgs(333, 107);
      int returnValueA = _componentA->VirtualNonVoid();
      int returnValueB = _componentA->VirtualNonVoidConst();
      int sum = returnValueA + returnValueB;
      return sum;
   }
};

TESTS(ClassUnderTestTests)
SPEC(Constructor_NewsComponentA)
SPECX(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues)
SPECEND

ClassUnderTest _classUnderTest;
ComponentAMock* _componentAMock;

STARTUP
{
   // Post-construction dependency injection (PCDI) of ZenMock object _componentAMock
   _classUnderTest._componentA.reset(_componentAMock = new ComponentAMock);
}

TEST(Constructor_NewsComponentA)
{
   ClassUnderTest classUnderTest;
   // WAS_NEWED operator deletes _componentA to confirm that it was operator newed
   WAS_NEWED(classUnderTest._componentA);
}

// A 3-by-3 value-parameterized test processes its variadic test case arguments
// 3-by-3, forming 9 independent test cases
TEST3X3(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues,
   int expectedReturnValue, int returnValueA, int returnValueB,
   0, 0, 0,
   0, -1, 1,
   10, 10, 0,
   10, 0, 10,
   20, 10, 10,
   30, 20, 10,
   30, 10, 20,
   -30, -10, -20,
   -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())
{
   // For reasons of imperviousness to extraneous-call code mutations
   // capable of being automatically introduced by future LLVM-powered
   // mutation testing frameworks, ZenMock is a strict mocking framework.
   // Because of this strict mocking design, ZenMock mock objects must be
   // explicitly expected before being called by calling
   // Expect(), ExpectAndReturn(), ExpectAndReturnValues(), or ExpectAndThrow<T>().
   _componentAMock->VirtualVoidMock.Expect();
   _componentAMock->VirtualVoidConstTwoArgsMock.Expect();
   _componentAMock->VirtualNonVoidMock.ExpectAndReturn(returnValueA);
   _componentAMock->VirtualNonVoidConstMock.ExpectAndReturn(returnValueB);
   //
   int returnValue = _classUnderTest.InteractWithComponentA();
   //
   // In the Assert section of this Arrange-Act-Assert style of unit test,
   // ZenMock function call assertions are made and are wrapped with the ZEN macro.
   // The ZEN macro wrapper provides __FILE__ and __LINE__ information
   // for the case when a ZenMocked function is called differently from how it is asserted
   // to have been called - such as by too many calls or a mismatching function argument.
   ZEN(_componentAMock->VirtualVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualVoidConstTwoArgsMock.AssertCalledOnceWith(333, 107));
   ZEN(_componentAMock->VirtualNonVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualNonVoidConstMock.AssertCalledOnce());
   ARE_EQUAL(expectedReturnValue, returnValue);
}

}; RUN(ClassUnderTestTests)
