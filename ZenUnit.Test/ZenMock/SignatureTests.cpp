#include "pch.h"
#include "ZenUnit/ZenMock/Signature.h"

namespace ZenMock
{
   TESTS(SignatureTests)
   SPECX(Function_ReturnsFunctionSignature)
   SPEC(FunctionPointer_ReturnsExpected)
   SPECEND

   TEST3X3(Function_ReturnsFunctionSignature,
      string expectedFunctionSignature, const char* virtualOrEmptyString, const char* constOrEmptyString,
      "int ZenMockedClassName::Function(int, double)", "", "",
      "virtual int ZenMockedClassName::Function(int, double)", "virtual", "",
      "int ZenMockedClassName::Function(int, double) const", "", "const",
      "virtual int ZenMockedClassName::Function(int, double) const", "virtual", "const")
   {
      const char* ReturnType = "int";
      const string ZenMockedClassName = "ZenMockedClassName";
      const char* UnadornedFunctionSignature = "Function(int, double)";
      //
      string funtionSignature = Signature::Function(
         virtualOrEmptyString, ReturnType, &ZenMockedClassName, UnadornedFunctionSignature, constOrEmptyString);
      //
      ARE_EQUAL(expectedFunctionSignature, funtionSignature);
   }

   TEST(FunctionPointer_ReturnsExpected)
   {
      const char* ReturnType = "ReturnType";
      const char* UnadornedFunctionSignature = "FunctionSignature";
      //
      string functionPointerSignature = Signature::FunctionPointer(ReturnType, UnadornedFunctionSignature);
      //
      ARE_EQUAL("ReturnType FunctionSignature", functionPointerSignature);
   }

   }; RUN(SignatureTests)
}
