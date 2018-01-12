#include "pch.h"

class ComponentA
{
public:
   virtual void VirtualVoid() {}
   virtual void VirtualVoidConstTwoArgs(int, int) const {}
   virtual int VirtualNonVoid() { return 0; }
   virtual int VirtualNonVoidConst() const { return 0; }
   virtual ~ComponentA() = default;
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
   virtual ~ComponentB() = default;
};

struct ComponentBMock : public Zen::Mock<ComponentB>
{
   ZENMOCK_VOID0_NONVIRTUAL(VoidFunction)
   ZENMOCK_VOID0_NONVIRTUAL_CONST(VoidFunctionConst)
   ZENMOCK_NONVOID0_NONVIRTUAL(int, NonVoidFunction)
   ZENMOCK_NONVOID0_NONVIRTUAL_CONST(int, NonVoidFunctionConst)
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
AFACT(Constructor_NewsComponentA)
FACTS(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues)
EVIDENCE

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
   // POINTER_WAS_NEWED operator deletes _componentA to confirm that it was operator newed
   POINTER_WAS_NEWED(classUnderTest._componentA);
}

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
   // ZenMock is a strict mocking framework for imperviousness to
   // extraneous-call code mutations capable of being automatically
   // introduced by future LLVM-powered mutation testing frameworks.
   // Because of this strict mocking design, ZenMock mock objects must be
   // explicitly expected before being called by calling either
   // Expect(), Return(), ReturnValues(), or Throw<ExceptionType>().
   _componentAMock->VirtualVoidMock.Expect();
   _componentAMock->VirtualVoidConstTwoArgsMock.Expect();
   _componentAMock->VirtualNonVoidMock.Return(returnValueA);
   _componentAMock->VirtualNonVoidConstMock.Return(returnValueB);
   //
   int returnValue = _classUnderTest.InteractWithComponentA();
   //
   // In the Assert section of this Arrange-Act-Assert style of unit test,
   // ZenMock function call assertions are made and are wrapped with the ZEN macro.
   // The ZEN macro wrapper provides __FILE__ and __LINE__ information
   // for the case when a ZenMocked function is called differently from how it is asserted
   // to have been called - such as by too many calls or a mismatching function argument.
   ZEN(_componentAMock->VirtualVoidMock.CalledOnce());
   ZEN(_componentAMock->VirtualVoidConstTwoArgsMock.CalledOnceWith(333, 107));
   ZEN(_componentAMock->VirtualNonVoidMock.CalledOnce());
   ZEN(_componentAMock->VirtualNonVoidConstMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, returnValue);
}

}; RUNTESTS(ClassUnderTestTests)
