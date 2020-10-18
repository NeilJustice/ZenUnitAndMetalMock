#include "pch.h"

namespace VirtualFunctionMockingTestingNamespace
{
   class Widget
   {
   public:
      virtual void VoidZeroArgVirtualFunction() {}
      virtual void VoidZeroArgConstVirtualFunction() const {}

      virtual void VoidOneArgVirtualFunction(int) {}
      virtual void VoidOneArgConstVirtualFunction(int) const {}

      virtual int NonVoidZeroArgVirtualFunction() { return 0; }
      virtual int NonVoidZeroArgConstVirtualFunction() const { return 0; }

      virtual int NonVoidOneArgVirtualFunction(int) { return 0; }
      virtual int NonVoidOneArgConstVirtualFunction(int) const { return 0; }

      virtual ~Widget() = default;
   };

   TESTS(WidgetTestsForCodeCoverage)
   AFACT(AllFunctionsCalledForCodeCoverage)
   EVIDENCE

   TEST(AllFunctionsCalledForCodeCoverage)
   {
      Widget widget;
      widget.VoidZeroArgVirtualFunction();
      widget.VoidZeroArgConstVirtualFunction();
      widget.VoidOneArgVirtualFunction(ZenUnit::Random<int>());
      widget.VoidOneArgConstVirtualFunction(ZenUnit::Random<int>());
      widget.NonVoidZeroArgVirtualFunction();
      widget.NonVoidZeroArgConstVirtualFunction();
      widget.NonVoidOneArgVirtualFunction(ZenUnit::Random<int>());
      widget.NonVoidOneArgConstVirtualFunction(ZenUnit::Random<int>());
   }

   RUN_TESTS(WidgetTestsForCodeCoverage)


   class WidgetMock : public Metal::Mock<Widget>
   {
   public:
      METALMOCK_VOID0(VoidZeroArgVirtualFunction)
      METALMOCK_VOID0_CONST(VoidZeroArgConstVirtualFunction)

      METALMOCK_VOID1(VoidOneArgVirtualFunction, int)
      METALMOCK_VOID1_CONST(VoidOneArgConstVirtualFunction, int)

      METALMOCK_NONVOID0(int, NonVoidZeroArgVirtualFunction)
      METALMOCK_NONVOID0_CONST(int, NonVoidZeroArgConstVirtualFunction)

      METALMOCK_NONVOID1(int, NonVoidOneArgVirtualFunction, int)
      METALMOCK_NONVOID1_CONST(int, NonVoidOneArgConstVirtualFunction, int)
   };

   class ClassUnderTest
   {
      friend class TestsForClassUnderTest;
   private:
      std::unique_ptr<Widget> _widget = std::make_unique<Widget>();
   public:
      int FunctionUnderTest() const
      {
         _widget->VoidZeroArgVirtualFunction();
         _widget->VoidZeroArgConstVirtualFunction();

         _widget->VoidOneArgVirtualFunction(1);
         _widget->VoidOneArgConstVirtualFunction(2);

         const int returnValue1 = _widget->NonVoidZeroArgVirtualFunction();
         const int returnValue2 = _widget->NonVoidZeroArgConstVirtualFunction();

         const int returnValue3A = _widget->NonVoidOneArgVirtualFunction(3);
         const int returnValue3B = _widget->NonVoidOneArgVirtualFunction(3);
         const int returnValue3C = _widget->NonVoidOneArgVirtualFunction(3);

         const int returnValue4A = _widget->NonVoidOneArgConstVirtualFunction(4);
         const int returnValue4B = _widget->NonVoidOneArgConstVirtualFunction(4);
         const int returnValue4C = _widget->NonVoidOneArgConstVirtualFunction(4);

         const int sumOfReturnValues =
            returnValue1 + returnValue2 +
            returnValue3A + returnValue3B + returnValue3C +
            returnValue4A + returnValue4B + returnValue4C;
         return sumOfReturnValues;
      }
   };

   TESTS(TestsForClassUnderTest)
   AFACT(FunctionUnderTest_CallsAllWidgetFunctions_ReturnsTheSumOfWidgetReturnValues)
   EVIDENCE

   ClassUnderTest _classUnderTest;
   WidgetMock* _widgetMock = nullptr;

   STARTUP
   {
      // Dependency injection of MetalMock object _widgetMock
      _classUnderTest._widget.reset(_widgetMock = new WidgetMock);
   }

   TEST(FunctionUnderTest_CallsAllWidgetFunctions_ReturnsTheSumOfWidgetReturnValues)
   {
      // MetalMockObject.Expect() and the MetalMockObject.Return() family of functions
      // enable MetalMockObject.MetalMockedFunction()
      // to be called without a MetalMock::UnexpectedCallAssertion being thrown.
      _widgetMock->VoidZeroArgVirtualFunctionMock.Expect();
      _widgetMock->VoidZeroArgConstVirtualFunctionMock.Expect();

      _widgetMock->VoidOneArgVirtualFunctionMock.Expect();
      _widgetMock->VoidOneArgConstVirtualFunctionMock.Expect();

      // MetalMockObject.Return(value) makes the MetalMocked function return value.
      const int returnValue1 = 1;
      _widgetMock->NonVoidZeroArgVirtualFunctionMock.Return(1);

      // MetalMockObject.ReturnRandom() makes the MetalMocked function
      // return a ZenUnit::Random<MetalMockedFunctionReturnType>() on each call.
      const int returnValue2 = _widgetMock->NonVoidZeroArgConstVirtualFunctionMock.ReturnRandom();

      // MetalMockObject.ReturnValues(valuesContainer) makes the MetalMocked function
      // return each value in valuesContainer then the last value of valuesContainer thereafter.
      const std::vector<int> returnValues3AThrough3C = { 3, 4 };
      _widgetMock->NonVoidOneArgVirtualFunctionMock.ReturnValues(returnValues3AThrough3C);

      // MetalMockObject.ReturnValues(values...) makes the MetalMocked function
      // return each value in values... then the last value of values... thereafter.
      const int returnValue4A = 5;
      const int returnValue4BAnd4C = 6;
      _widgetMock->NonVoidOneArgConstVirtualFunctionMock.ReturnValues(returnValue4A, returnValue4BAnd4C);
      //
      const int sumOfWidgetReturnValues = _classUnderTest.FunctionUnderTest();
      //
      // ZEN augments potential assertion-failed error messages with __FILE__ and __LINE__ information.
      METALMOCK(_widgetMock->VoidZeroArgVirtualFunctionMock.CalledOnce());
      METALMOCK(_widgetMock->VoidZeroArgConstVirtualFunctionMock.CalledOnce());
      METALMOCK(_widgetMock->VoidOneArgVirtualFunctionMock.CalledOnceWith(1));
      METALMOCK(_widgetMock->VoidOneArgConstVirtualFunctionMock.CalledOnceWith(2));
      METALMOCK(_widgetMock->NonVoidZeroArgVirtualFunctionMock.CalledOnce());
      METALMOCK(_widgetMock->NonVoidZeroArgConstVirtualFunctionMock.CalledOnce());
      METALMOCK(_widgetMock->NonVoidOneArgVirtualFunctionMock.CalledNTimesWith(3, 3));
      METALMOCK(_widgetMock->NonVoidOneArgConstVirtualFunctionMock.CalledNTimesWith(3, 4));
      const int expectedSumOfWidgetReturnValues =
         returnValue1 + returnValue2 +
         returnValues3AThrough3C[0] + returnValues3AThrough3C[1] + returnValues3AThrough3C[1] +
         returnValue4A + returnValue4BAnd4C + returnValue4BAnd4C;
      ARE_EQUAL(expectedSumOfWidgetReturnValues, sumOfWidgetReturnValues);
   }

   RUN_TESTS(TestsForClassUnderTest)
}
