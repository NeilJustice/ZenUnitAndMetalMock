#pragma once
#include "ZenMockTests/ZenMock/ZenMockTestUtil.h"

namespace ZenMock
{
   template<
      typename ZenMockObjectType,
      typename FreeFunctionMockType,
      typename NamespacedFreeFunctionMockType,
      typename StaticFunctionMockType>
   class ZenMock2ArgTester
   {
   private:
      ZenMockObjectType zenMockObject;

      const string virtualFunctionSignature;
      const string virtualFunctionConstSignature;
      const string nonVirtualFunctionSignature;
      const string nonVirtualFunctionConstSignature;

      FreeFunctionMockType freeFunctionMock;
      const string freeFunctionSignature;

      NamespacedFreeFunctionMockType namespacedFreeFunctionMock;
      const string namespacedFreeFunctionSignature;

      StaticFunctionMockType staticFunctionMock;
      const string staticFunctionSignature;
   public:
      ZenMock2ArgTester(
         ZenMockObjectType zenMockObject,
         string virtualFunctionSignature,
         string virtualFunctionConstSignature,
         string nonVirtualFunctionSignature,
         string nonVirtualFunctionConstSignature,

         FreeFunctionMockType freeFunctionMock,
         string freeFunctionSignature,

         NamespacedFreeFunctionMockType namespacedFreeFunctionMock,
         string namespacedFreeFunctionSignature,

         StaticFunctionMockType staticFunctionMock,
         string staticFunctionSignature)
         : zenMockObject(move(zenMockObject))
         , virtualFunctionSignature(move(virtualFunctionSignature))
         , virtualFunctionConstSignature(move(virtualFunctionConstSignature))
         , nonVirtualFunctionSignature(move(nonVirtualFunctionSignature))
         , nonVirtualFunctionConstSignature(move(nonVirtualFunctionConstSignature))

         , freeFunctionMock(move(freeFunctionMock))
         , freeFunctionSignature(move(freeFunctionSignature))

         , namespacedFreeFunctionMock(move(namespacedFreeFunctionMock))
         , namespacedFreeFunctionSignature(move(namespacedFreeFunctionSignature))

         , staticFunctionMock(move(staticFunctionMock))
         , staticFunctionSignature(move(staticFunctionSignature))
      {
      }

      void ZenMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto testcase = [](auto zenMockObjectFunctionCallLambda, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnexpectedCallException::MakeWhat(expectedFunctionSignature, 0);
            THROWS(zenMockObjectFunctionCallLambda(), UnexpectedCallException, expectedExceptionMessage);
         };
         testcase([&] { zenMockObject.Virtual(0); }, virtualFunctionSignature);
         testcase([&] { zenMockObject.VirtualConst(0); }, virtualFunctionConstSignature);
         testcase([&] { zenMockObject.NonVirtual(0); }, nonVirtualFunctionSignature);
         testcase([&] { zenMockObject.NonVirtualConst(0); }, nonVirtualFunctionConstSignature);

         function<void(int)> zenMockBoundFreeFunctionMock = BIND_1ARG_ZENMOCK_OBJECT(freeFunctionMock);
         testcase([&] { zenMockBoundFreeFunctionMock(0); }, freeFunctionSignature);

         function<void(int)> zenMockBoundNamespacedFreeFunctionMock = BIND_1ARG_ZENMOCK_OBJECT(namespacedFreeFunctionMock);
         testcase([&] { zenMockBoundNamespacedFreeFunctionMock(0); }, namespacedFreeFunctionSignature);

         function<void(int)> zenMockBoundStaticFunctionMock = BIND_1ARG_ZENMOCK_OBJECT(staticFunctionMock);
         testcase([&] { zenMockBoundStaticFunctionMock(0); }, staticFunctionSignature);
      }

      void ZenMockedFunction_Expected_DoesNotThrow()
      {
         const auto testcase = [](auto& zenMockObject)
         {
            zenMockObject._wasExpected = true;
            //
            zenMockObject.ZenMockIt(0, 0);
            //
            zenMockObject.CalledOnceWith(0, 0);
         };
         testcase(zenMockObject.VirtualFunctionMock);
         testcase(zenMockObject.VirtualConstFunctionMock);
         testcase(zenMockObject.NonVirtualFunctionMock);
         testcase(zenMockObject.NonVirtualConstFunctionMock);

         testcase(freeFunctionMock);
         testcase(namespacedFreeFunctionMock);
         testcase(staticFunctionMock);
      }
   };
}
