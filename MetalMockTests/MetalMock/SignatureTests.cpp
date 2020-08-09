#include "pch.h"

namespace MetalMock
{
   TESTS(FunctionSignatureTests)
   FACTS(Function_ReturnsFunctionSignature)
   FACTS(FunctionPointer_ReturnsExpected)
   EVIDENCE

   TEST6X6(Function_ReturnsFunctionSignature,
      string expectedFunctionSignature,
      const char* virtualOrEmptyString,
      const char* returnType,
      string metalMockedClassName,
      const char* unadornedFunctionSignature,
      const char* constOrEmptyString,
      "int MetalMockedClassNameA::Function(int)",
      "", "int", "MetalMockedClassNameA", "Function(int)", "",
      "virtual char MetalMockedClassNameB::Function(int, int)",
      "virtual", "char", "MetalMockedClassNameB", "Function(int, int)", "",
      "double MetalMockedClassNameC::Function() const",
      "", "double", "MetalMockedClassNameC", "Function()", "const",
      "virtual pair<int, int> MetalMockedClassNameD::Function(const pair<int, int>&) const",
      "virtual", "pair<int, int>", "MetalMockedClassNameD", "Function(const pair<int, int>&)", "const")
   {
      const string funtionSignature = FunctionSignature::Function(
         virtualOrEmptyString, returnType, &metalMockedClassName, unadornedFunctionSignature, constOrEmptyString);
      ARE_EQUAL(expectedFunctionSignature, funtionSignature);
   }

   TEST3X3(FunctionPointer_ReturnsExpected,
      string expectedFunctionPointerSignature, const char* returnType, const char* unadornedFunctionSignature,
      "FunctionReturnType FunctionNameA()", "FunctionReturnType", "FunctionNameA()",
      "int FunctionNameB(int)", "int", "FunctionNameB(int)")
   {
      const string functionPointerSignature = FunctionSignature::FunctionPointer(returnType, unadornedFunctionSignature);
      ARE_EQUAL(expectedFunctionPointerSignature, functionPointerSignature);
   }

   RUN_TESTS(FunctionSignatureTests)
}
