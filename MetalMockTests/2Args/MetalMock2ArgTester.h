#pragma once

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType>
   class MetalMock2ArgTester
   {
   private:
      MetalMockObjectType metalMockObject;
      const string virtualFunctionSignature;
      const string virtualFunctionConstSignature;
      const string nonVirtualFunctionSignature;
      const string nonVirtualFunctionConstSignature;

      FreeFunctionMockObjectType freeFunctionMockObject;
      const string freeFunctionSignature;

      StaticFunctionMockObjectType staticFunctionMockObject;
      const string staticFunctionSignature;
   public:
      MetalMock2ArgTester(
         MetalMockObjectType metalMockObject,
         string virtualFunctionSignature,
         string virtualFunctionConstSignature,
         string nonVirtualFunctionSignature,
         string nonVirtualFunctionConstSignature,

         FreeFunctionMockObjectType freeFunctionMockObject,
         string freeFunctionSignature,

         StaticFunctionMockObjectType staticFunctionMockObject,
         string staticFunctionSignature)
         : metalMockObject(std::move(metalMockObject))
         , virtualFunctionSignature(std::move(virtualFunctionSignature))
         , virtualFunctionConstSignature(std::move(virtualFunctionConstSignature))
         , nonVirtualFunctionSignature(std::move(nonVirtualFunctionSignature))
         , nonVirtualFunctionConstSignature(std::move(nonVirtualFunctionConstSignature))

         , freeFunctionMockObject(std::move(freeFunctionMockObject))
         , freeFunctionSignature(std::move(freeFunctionSignature))

         , staticFunctionMockObject(std::move(staticFunctionMockObject))
         , staticFunctionSignature(std::move(staticFunctionSignature))
      {
      }

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto testcase = [](auto metalMockObjectFunctionCallLambda, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(expectedFunctionSignature, 0);
            THROWS_EXCEPTION(metalMockObjectFunctionCallLambda(), UnexpectedCallException, expectedExceptionMessage);
         };
         testcase([&] { metalMockObject.Virtual(0); }, virtualFunctionSignature);
         testcase([&] { metalMockObject.VirtualConst(0); }, virtualFunctionConstSignature);
         testcase([&] { metalMockObject.NonVirtual(0); }, nonVirtualFunctionSignature);
         testcase([&] { metalMockObject.NonVirtualConst(0); }, nonVirtualFunctionConstSignature);

         function<void(int)> metalMockBoundFreeFunctionMock = BIND_1ARG_METALMOCK_OBJECT(freeFunctionMockObject);
         testcase([&] { metalMockBoundFreeFunctionMock(0); }, freeFunctionSignature);

         function<void(int)> metalMockBoundStaticFunctionMock = BIND_1ARG_METALMOCK_OBJECT(staticFunctionMockObject);
         testcase([&] { metalMockBoundStaticFunctionMock(0); }, staticFunctionSignature);
      }

      void MetalMockedFunction_Expected_DoesNotThrowException()
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

         testcase(freeFunctionMockObject);
         testcase(staticFunctionMockObject);
      }
   };
}
