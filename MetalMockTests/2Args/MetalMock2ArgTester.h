#pragma once
#include "MetalMockTests/MetalMock/MetalMockTestUtil.h"

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockType,
      typename NamespacedFreeFunctionMockType,
      typename StaticFunctionMockType>
   class MetalMock2ArgTester
   {
   private:
      MetalMockObjectType metalMockObject;

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
      MetalMock2ArgTester(
         MetalMockObjectType metalMockObject,
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
         : metalMockObject(std::move(metalMockObject))
         , virtualFunctionSignature(std::move(virtualFunctionSignature))
         , virtualFunctionConstSignature(std::move(virtualFunctionConstSignature))
         , nonVirtualFunctionSignature(std::move(nonVirtualFunctionSignature))
         , nonVirtualFunctionConstSignature(std::move(nonVirtualFunctionConstSignature))

         , freeFunctionMock(std::move(freeFunctionMock))
         , freeFunctionSignature(std::move(freeFunctionSignature))

         , namespacedFreeFunctionMock(std::move(namespacedFreeFunctionMock))
         , namespacedFreeFunctionSignature(std::move(namespacedFreeFunctionSignature))

         , staticFunctionMock(std::move(staticFunctionMock))
         , staticFunctionSignature(std::move(staticFunctionSignature))
      {
      }

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto testcase = [](auto metalMockObjectFunctionCallLambda, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnexpectedCallException::MakeWhat(expectedFunctionSignature, 0);
            THROWS_EXCEPTION(metalMockObjectFunctionCallLambda(), UnexpectedCallException, expectedExceptionMessage);
         };
         testcase([&] { metalMockObject.Virtual(0); }, virtualFunctionSignature);
         testcase([&] { metalMockObject.VirtualConst(0); }, virtualFunctionConstSignature);
         testcase([&] { metalMockObject.NonVirtual(0); }, nonVirtualFunctionSignature);
         testcase([&] { metalMockObject.NonVirtualConst(0); }, nonVirtualFunctionConstSignature);

         function<void(int)> metalMockBoundFreeFunctionMock = BIND_1ARG_METALMOCK_OBJECT(freeFunctionMock);
         testcase([&] { metalMockBoundFreeFunctionMock(0); }, freeFunctionSignature);

         function<void(int)> metalMockBoundNamespacedFreeFunctionMock = BIND_1ARG_METALMOCK_OBJECT(namespacedFreeFunctionMock);
         testcase([&] { metalMockBoundNamespacedFreeFunctionMock(0); }, namespacedFreeFunctionSignature);

         function<void(int)> metalMockBoundStaticFunctionMock = BIND_1ARG_METALMOCK_OBJECT(staticFunctionMock);
         testcase([&] { metalMockBoundStaticFunctionMock(0); }, staticFunctionSignature);
      }

      void MetalMockedFunction_Expected_DoesNotThrow()
      {
         const auto testcase = [](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            //
            metalMockObject.MetalMockIt(0, 0);
            //
            metalMockObject.CalledOnceWith(0, 0);
         };
         testcase(metalMockObject.VirtualFunctionMock);
         testcase(metalMockObject.VirtualConstFunctionMock);
         testcase(metalMockObject.NonVirtualFunctionMock);
         testcase(metalMockObject.NonVirtualConstFunctionMock);

         testcase(freeFunctionMock);
         testcase(namespacedFreeFunctionMock);
         testcase(staticFunctionMock);
      }
   };
}
