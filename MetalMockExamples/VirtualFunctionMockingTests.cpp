#include "pch.h"

// Component to be MetalMocked
class ComponentB
{
public:
   virtual void ConstVirtualFunction() const {}
   virtual void NonConstVirtualFunction() {}
   virtual ~ComponentB() = default;
};

// Class under test
class ComponentA
{
   friend class ComponentATests;
private:
   // ComponentB will be dependency injected with ComponentBMock in the below ZenUnit SETUP function
   std::unique_ptr<ComponentB> _componentB;
public:
   ComponentA()
      : _componentB(std::make_unique<ComponentB>())
   {
   }

   // Function under test
   void Act()
   {
      _componentB->ConstVirtualFunction();
      _componentB->NonConstVirtualFunction();
   }
};

// MetalMock class definition
class ComponentBMock : public Metal::Mock<ComponentB>
{
public:
   METALMOCK_VOID0_CONST(ConstVirtualFunction)
   METALMOCK_VOID0(NonConstVirtualFunction)
};

// ZenUnit test class
TESTS(ComponentATests)
AFACT(DefaultConstructor_NewsComponentB)
AFACT(Act_CallsComponentBVirtualFunctions)
EVIDENCE

ComponentA _componentA;
ComponentBMock* _componentBMock = nullptr;

STARTUP
{
   // Post-construction dependency injection of MetalMock mock object ComponentBMock
   _componentA._componentB.reset(_componentBMock = new ComponentBMock);
}

TEST(DefaultConstructor_NewsComponentB)
{
   DELETE_TO_ASSERT_NEWED(_componentA._componentB);
}

TEST(Act_CallsComponentBVirtualFunctions)
{
   _componentBMock->ConstVirtualFunctionMock.Expect();
   _componentBMock->NonConstVirtualFunctionMock.Expect();
   //
   _componentA.Act();
   //
   METALMOCK(_componentBMock->ConstVirtualFunctionMock.CalledOnce());
   METALMOCK(_componentBMock->NonConstVirtualFunctionMock.CalledOnce());
}

RUN_TESTS(ComponentATests)


TESTS(ComponentBTests)
AFACT(FunctionCodeCoverage)
EVIDENCE

TEST(FunctionCodeCoverage)
{
   ComponentB componentB;
   componentB.ConstVirtualFunction();
   componentB.NonConstVirtualFunction();
}

RUN_TESTS(ComponentBTests)
