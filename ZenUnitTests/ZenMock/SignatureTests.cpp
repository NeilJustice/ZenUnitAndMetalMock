#include "pch.h"
#include "ZenUnit/ZenMock/Signature.h"

namespace ZenMock
{
   TESTS(SignatureTests)
   FACTS(Function_ReturnsFunctionSignature)
   FACTS(FunctionPointer_ReturnsExpected)
   EVIDENCE

   TEST6X6(Function_ReturnsFunctionSignature,
      string expectedFunctionSignature,
      const char* virtualOrEmptyString,
      const char* returnType,
      string zenMockedClassName,
      const char* unadornedFunctionSignature,
      const char* constOrEmptyString,
      "int ZenMockedClassNameA::Function(int)",
         "", "int", "ZenMockedClassNameA", "Function(int)", "",
      "virtual char ZenMockedClassNameB::Function(int, int)",
         "virtual", "char", "ZenMockedClassNameB", "Function(int, int)", "",
      "double ZenMockedClassNameC::Function() const",
         "", "double", "ZenMockedClassNameC", "Function()", "const",
      "virtual pair<int, int> ZenMockedClassNameD::Function(const pair<int, int>&) const",
         "virtual", "pair<int, int>", "ZenMockedClassNameD", "Function(const pair<int, int>&)", "const")
   {
      const string funtionSignature = Signature::Function(
         virtualOrEmptyString, returnType, &zenMockedClassName, unadornedFunctionSignature, constOrEmptyString);
      ARE_EQUAL(expectedFunctionSignature, funtionSignature);
   }

   TEST3X3(FunctionPointer_ReturnsExpected,
      string expectedFunctionPointerSignature, const char* returnType, const char* unadornedFunctionSignature,
      "ReturnType FunctionNameA()", "ReturnType", "FunctionNameA()",
      "int FunctionNameB(int)", "int", "FunctionNameB(int)")
   {
      const string functionPointerSignature = Signature::FunctionPointer(returnType, unadornedFunctionSignature);
      ARE_EQUAL(expectedFunctionPointerSignature, functionPointerSignature);
   }

   RUNTESTS(SignatureTests)
}
