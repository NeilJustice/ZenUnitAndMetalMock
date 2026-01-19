#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Assertions/REGEX_MATCHES.h"
#include "ZenUnitTestUtils/UserType.h"
#include "ZenUnitTestUtils/DoublyPrintableUserType.h"
#include "ZenUnitTestUtils/NonPrintableUserType.h"
#include "ZenUnitTestUtils/OnlyZenUnitPrintableUserType.h"

namespace ZenUnit
{
   struct ToStringerTestStruct
   {
      int value;
      mutable int argValue = 0;
      mutable size_t numberOfFunctionCalls = 0;

      explicit ToStringerTestStruct(int value)
         : value(value)
      {
      }

      friend ostream& operator<<(ostream& os, const ToStringerTestStruct& sts)
      {
         ++sts.numberOfFunctionCalls;
         sts.argValue = sts.value;
         return os;
      }

      void AssertInsertionOperatorCalledOnceWith(int expectedValue)
      {
         ARE_EQUAL(1, numberOfFunctionCalls);
         ARE_EQUAL(expectedValue, argValue);
      }
   };

   enum ClassicEnum { E0, E1 }; // NOLINT
   enum class EnumClass : long long
   {
      EC0,
      EC1 = static_cast<long long>(numeric_limits<int>::max()) + 1
   };

   TESTS(ToStringerTests)
   AFACT(ToString_Arithmetic_ReturnsResultOfStdToString)
   AFACT(ToString_Float_Returns6PrecisionString)
   AFACT(ToString_Double_Returns15PrecisionString)
   AFACT(ToString_Enum_ReturnsStdToStringOnTheValue)
   AFACT(ToString_EnumClass_ReturnsStdToStringOnTheValue)
   AFACT(ToString_Nullptr_ReturnsNullptrInBrackets)
   AFACT(ToString_NonArithmeticType_ReturnsInsertionOperatorValue)
   AFACT(ToString_Pointer_ReturnsNullptrIfNullptrOtherwiseMemoryAddress)
   AFACT(ToString_UniquePtr_ReturnsPointeeAddress)
   AFACT(ToString_UniquePtrWithCustomDeleter_ReturnsPointeeAddress)
   AFACT(ToString_SharedPtr_ReturnsPointeeAddress)
   FACTS(ToString_VoidZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction)
   FACTS(ToString_NonVoidNonZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction)
   AFACT(ToString_StdString_ReturnsQuotedString)
   AFACT(ToString_CharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   AFACT(ToString_ConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   AFACT(ToString_WideCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   AFACT(ToString_WideConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   AFACT(ToString_Char_ReturnsQuotedChar)
   AFACT(ToString_Bool_ReturnsBoolAlpha)
   AFACT(ToString_Pair_ReturnsLeftParenFirstValueCommaSecondValueRightParen)
   AFACT(ToString_TypeDoesNotHaveZenUnitPrinter_TypeDoesNotHaveOStreamInsertionOperator_ReturnsRTTITypeNameInBrackets)
   AFACT(ToString_TypeDoesNotHaveZenUnitPrinter_TypeHasOStreamInsertionOperator_ReturnsOStreamLeftShiftResult)
   AFACT(ToString_TypeHasZenUnitPrinter_TypeDoesNotHaveOStreamInsertionOperator_ReturnsZenUnitPrinterResult)
   AFACT(ToString_TypeHasZenUnitPrinter_TypeHasOStreamInsertionOperator_ReturnsZenUnitPrinterResult)
   AFACT(ToStringConcat_ReturnsCommaSeparatedToStringedValues)
   EVIDENCE

   TEST(ToString_Arithmetic_ReturnsResultOfStdToString)
   {
      ARE_EQUAL("-1", ToStringer::ToString(-1));
      ARE_EQUAL("0", ToStringer::ToString(0));
      ARE_EQUAL("1", ToStringer::ToString(1));
   }

   TEST(ToString_Float_Returns6PrecisionString)
   {
      ARE_EQUAL("-0.123456", ToStringer::ToString(-0.123456f));
      ARE_EQUAL("-1.12346", ToStringer::ToString(-1.123456f));
      ARE_EQUAL("-1e-06", ToStringer::ToString(-0.000001f));
      ARE_EQUAL("0", ToStringer::ToString(0.0f));
      ARE_EQUAL("1e-06", ToStringer::ToString(0.000001f));
      ARE_EQUAL("1.1", ToStringer::ToString(1.1f));
      ARE_EQUAL("0.123456", ToStringer::ToString(0.123456f));
      ARE_EQUAL("1.12346", ToStringer::ToString(1.123456f));
   }

   TEST(ToString_Double_Returns15PrecisionString)
   {
      ARE_EQUAL("-1.12345678901235", ToStringer::ToString(-1.123456789012345));
      ARE_EQUAL("-0.123456789012345", ToStringer::ToString(-0.123456789012345));
      ARE_EQUAL("-1e-15", ToStringer::ToString(-0.000000000000001));
      ARE_EQUAL("0", ToStringer::ToString(0.0));
      ARE_EQUAL("1e-15", ToStringer::ToString(0.000000000000001));
      ARE_EQUAL("1.1", ToStringer::ToString(1.1));
      ARE_EQUAL("0.123456789012345", ToStringer::ToString(0.123456789012345));
      ARE_EQUAL("1.12345678901235", ToStringer::ToString(1.123456789012345));
   }

   TEST(ToString_Enum_ReturnsStdToStringOnTheValue)
   {
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 26812)
      ARE_EQUAL("0", ToStringer::ToString(ClassicEnum::E0));
#pragma warning(pop)
#endif
      ARE_EQUAL("1", ToStringer::ToString(ClassicEnum::E1));
   }

   TEST(ToString_EnumClass_ReturnsStdToStringOnTheValue)
   {
      ARE_EQUAL("0", ToStringer::ToString(EnumClass::EC0));
      const string expected = to_string(static_cast<long long>(numeric_limits<int>::max()) + 1);
      ARE_EQUAL("2147483648", expected);
      ARE_EQUAL(expected, ToStringer::ToString(EnumClass::EC1));
   }

   TEST(ToString_Nullptr_ReturnsNullptrInBrackets)
   {
      nullptr_t nullPointerType = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(nullPointerType));
      ARE_EQUAL("nullptr", ToStringer::ToString(nullptr));
   }

   TEST(ToString_NonArithmeticType_ReturnsInsertionOperatorValue)
   {
      ToStringerTestStruct s(1);
      //
      const string str = ToStringer::ToString(s);
      //
      s.AssertInsertionOperatorCalledOnceWith(1);
      ARE_EQUAL("", str);
   }

   TEST(ToString_Pointer_ReturnsNullptrIfNullptrOtherwiseMemoryAddress)
   {
      const int* const intPointerNullptr = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(intPointerNullptr));

      const int* const constIntPointerNullptr = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(constIntPointerNullptr));

      const int* const constIntPointerNullptrConst = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(constIntPointerNullptrConst));

#if defined __linux__
      int* intPointer1 = reinterpret_cast<int*>(0x1);
      ARE_EQUAL("0x1", ToStringer::ToString(intPointer1));
      int* intPointerFF = reinterpret_cast<int*>(0xFF);
      ARE_EQUAL("0xff", ToStringer::ToString(intPointerFF));
      int* intPointerMaxAsHex = reinterpret_cast<int*>(0xFFFFFFFFFFFFFFFF);
      ARE_EQUAL("0xffffffffffffffff", ToStringer::ToString(intPointerMaxAsHex));
      int* intPointerMaxAsBinary = reinterpret_cast<int*>(0b1111111111111111111111111111111111111111111111111111111111111111);
      ARE_EQUAL("0xffffffffffffffff", ToStringer::ToString(intPointerMaxAsBinary));
      const int* intPointerMid = reinterpret_cast<const int*>(0x1111111111111111);
      ARE_EQUAL("0x1111111111111111", ToStringer::ToString(intPointerMid));
#elif defined _WIN32
      const int* const intPointer1 = reinterpret_cast<const int*>(0x1);
      ARE_EQUAL("0x0000000000000001", ToStringer::ToString(intPointer1));
      const int* const intPointerFF = reinterpret_cast<const int*>(0xFF);
      ARE_EQUAL("0x00000000000000FF", ToStringer::ToString(intPointerFF));
      const int* const intPointerMaxAsHex = reinterpret_cast<const int*>(0xFFFFFFFFFFFFFFFF);
      ARE_EQUAL("0xFFFFFFFFFFFFFFFF", ToStringer::ToString(intPointerMaxAsHex));
      const int* intPointerMaxAsBinary = reinterpret_cast<const int*>(0b1111111111111111111111111111111111111111111111111111111111111111);
      ARE_EQUAL("0xFFFFFFFFFFFFFFFF", ToStringer::ToString(intPointerMaxAsBinary));
      const int* intPointerMid = reinterpret_cast<const int*>(0x1111111111111111);
      ARE_EQUAL("0x1111111111111111", ToStringer::ToString(intPointerMid));
#endif
   }

   TEST(ToString_UniquePtr_ReturnsPointeeAddress)
   {
      const unique_ptr<int> nullUniquePtr(nullptr);
      const string nullUniquePtrAsString = ToStringer::ToString(nullUniquePtr);
      ARE_EQUAL("nullptr", nullUniquePtrAsString);

      const unique_ptr<int> nonNullUniquePtr(new int);
      const string nonNullUniquePtrString = ToStringer::ToString(nonNullUniquePtr);
      REGEX_MATCHES(MemoryAddressPattern(), nonNullUniquePtrString);

      const unique_ptr<const int> constNonNullUniquePtr(new int);
      const string constNonNullUniquePtrString = ToStringer::ToString(constNonNullUniquePtr);
      REGEX_MATCHES(MemoryAddressPattern(), constNonNullUniquePtrString);
   }

   struct CustomDeleter
   {
      template<typename T>
      void operator()(T* ptr)
      {
         delete ptr;
      }
   };

   TEST(ToString_UniquePtrWithCustomDeleter_ReturnsPointeeAddress)
   {
      const unique_ptr<int, CustomDeleter> nullUniquePtr(nullptr);
      ARE_EQUAL("nullptr", ToStringer::ToString(nullUniquePtr));

      const unique_ptr<int, CustomDeleter> nonNullUniquePtr(new int);
      const string nonNullUniquePtrString = ToStringer::ToString(nonNullUniquePtr);
      REGEX_MATCHES(MemoryAddressPattern(), nonNullUniquePtrString);

      const unique_ptr<const int, CustomDeleter> constNonNullUniquePtr(new int);
      const string constNonNullUniquePtrString = ToStringer::ToString(constNonNullUniquePtr);
      REGEX_MATCHES(MemoryAddressPattern(), constNonNullUniquePtrString);
   }

   static const char* MemoryAddressPattern()
   {
#if defined __linux__
      return R"(0x\w+)";
#elif defined _WIN32
      return R"(0x\w\w\w\w\w\w\w\w\w\w\w\w\w\w\w\w)";
#endif
   }

   TEST(ToString_SharedPtr_ReturnsPointeeAddress)
   {
      const shared_ptr<const int> nullSharedPtr(nullptr);
      const string nullSharedPtrAsString = ToStringer::ToString(nullSharedPtr);
      ARE_EQUAL("nullptr", nullSharedPtrAsString);

      const shared_ptr<const int> nonNullSharedPtr(new int);
      const string nonNullSharedPtrString = ToStringer::ToString(nonNullSharedPtr);
      REGEX_MATCHES(MemoryAddressPattern(), nonNullSharedPtrString);

      const shared_ptr<const int> constNonNullSharedPtr(new int);
      const string constNonNullSharedPtrString = ToStringer::ToString(constNonNullSharedPtr);
      REGEX_MATCHES(MemoryAddressPattern(), constNonNullSharedPtrString);
   }

   TEST2X2(ToString_VoidZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction,
      string expectedReturnValue, bool stdFunctionIsEmpty,
      "<empty std::function>", true,
      "<non-empty std::function>", false)
   {
      function<void()> stdFunction;
      if (!stdFunctionIsEmpty)
      {
         stdFunction = []{};
         stdFunction(); // Lambda code coverage
      }
      ARE_EQUAL(expectedReturnValue, ToStringer::ToString(stdFunction));
   }

   TEST2X2(ToString_NonVoidNonZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction,
      string expectedReturnValue, bool stdFunctionIsEmpty,
      "<empty std::function>", true,
      "<non-empty std::function>", false)
   {
      function<int(char, float, double)> stdFunction;
      if (!stdFunctionIsEmpty)
      {
         stdFunction = [](char, float, double) { return 0; };
         stdFunction('a', 10.0f, 20.0); // Lambda code coverage
      }
      ARE_EQUAL(expectedReturnValue, ToStringer::ToString(stdFunction));
   }

   TEST(ToString_StdString_ReturnsQuotedString)
   {
      const string str = ZenUnit::Random<string>();
      //
      const string toStringResult = ToStringer::ToString(str);
      //
      const string expectedToStringResult = "\"" + str + "\"";
      ARE_EQUAL(expectedToStringResult, toStringResult);
   }

   TEST(ToString_CharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      ARE_EQUAL("nullptr", ToStringer::ToString(static_cast<char*>(nullptr)));

      const array<char, 1> chars { 0 };
      ARE_EQUAL("\"\"", ToStringer::ToString(const_cast<char*>(chars.data())));

      const array<char, 4> charsABC { 'A', 'B', 'C', 0 };
      ARE_EQUAL("\"ABC\"", ToStringer::ToString(const_cast<char*>(charsABC.data())));

      char* const charPointer = const_cast<char*>("abc");
      ARE_EQUAL("\"abc\"", ToStringer::ToString(charPointer));
   }

   TEST(ToString_ConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      ARE_EQUAL("nullptr", ToStringer::ToString(static_cast<const char*>(nullptr)));
      ARE_EQUAL("\"\"", ToStringer::ToString(""));
      ARE_EQUAL("\"ABC\"", ToStringer::ToString("ABC"));

      const string expected = R"("a\b\c")";
      const string actual = ToStringer::ToString(R"(a\b\c)");
      ARE_EQUAL(expected, actual);
   }

   TEST(ToString_WideCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      const array<wchar_t, 1> chars { 0 };
      ARE_EQUAL("\"\"", ToStringer::ToString(chars.data()));

      const array<wchar_t, 4> charsABC { 'A', 'B', 'C', 0 };
      ARE_EQUAL("\"ABC\"", ToStringer::ToString(charsABC.data()));
   }

   TEST(ToString_WideConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      ARE_EQUAL("nullptr", ToStringer::ToString(static_cast<const wchar_t*>(nullptr)));
      ARE_EQUAL("\"\"", ToStringer::ToString(L""));
      ARE_EQUAL("\".\"", ToStringer::ToString(L"."));

      const string expected = R"("a\b\c")";
      const string actual = ToStringer::ToString(L"a\\b\\c");
      ARE_EQUAL(expected, actual);

      ARE_EQUAL("\"a/b/c\"", ToStringer::ToString(L"a/b/c"));
      ARE_EQUAL("\"ABC\"", ToStringer::ToString(L"ABC"));
   }

   TEST(ToString_Char_ReturnsQuotedChar)
   {
      ARE_EQUAL("'\\0' (0)", ToStringer::ToString(static_cast<char>(0)));
      ARE_EQUAL("'\\0' (0)", ToStringer::ToString(static_cast<char>('\0')));
      ARE_EQUAL("'a' (97)", ToStringer::ToString(static_cast<char>('a')));
      ARE_EQUAL("'0' (48)", ToStringer::ToString(static_cast<char>('0')));
      ARE_EQUAL("' ' (32)", ToStringer::ToString(static_cast<char>(' ')));
      ARE_EQUAL("'\n' (10)", ToStringer::ToString(static_cast<char>('\n')));
   }

   TEST(ToString_Bool_ReturnsBoolAlpha)
   {
      ARE_EQUAL("false", ToStringer::ToString(false));
      ARE_EQUAL("true", ToStringer::ToString(true));
   }

   TEST(ToString_Pair_ReturnsLeftParenFirstValueCommaSecondValueRightParen)
   {
      ARE_EQUAL("(0, 1)", ToStringer::ToString(pair<int, int>(0, 1)));
      ARE_EQUAL("(nullptr, nullptr)", ToStringer::ToString(pair<int*, int*>()));
      ARE_EQUAL("(nullptr, nullptr)", ToStringer::ToString(pair<const int*, const int*>()));
      ARE_EQUAL("(\"hello1\", \"hello2\")", ToStringer::ToString(pair<string, string>("hello1", "hello2")));
#if defined __linux__
      ARE_EQUAL("(0x1, 5)", ToStringer::ToString(pair<int*, int>(reinterpret_cast<int*>(0x1), 5)));
#elif defined _WIN32
      ARE_EQUAL("(0x0000000000000001, 5)", ToStringer::ToString(pair<int*, int>(reinterpret_cast<int*>(0x1), 5)));
#endif
   }

   TEST(ToString_TypeDoesNotHaveZenUnitPrinter_TypeDoesNotHaveOStreamInsertionOperator_ReturnsRTTITypeNameInBrackets)
   {
      const NonPrintableUserType nonPrintableUserType;
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(nonPrintableUserType);
      //
      ARE_EQUAL("<NonPrintableUserType>", toStringResult);
   }

   TEST(ToString_TypeDoesNotHaveZenUnitPrinter_TypeHasOStreamInsertionOperator_ReturnsOStreamLeftShiftResult)
   {
      const OnlyInsertionOperatorPrintableUserType onlyInsertionOperatorPrintableUserType(1);
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(onlyInsertionOperatorPrintableUserType);
      //
      ARE_EQUAL("OnlyInsertionOperatorPrintableUserType@1", toStringResult);
   }

   TEST(ToString_TypeHasZenUnitPrinter_TypeDoesNotHaveOStreamInsertionOperator_ReturnsZenUnitPrinterResult)
   {
      const OnlyZenUnitPrintableUserType onlyZenUnitPrintableUserType{};
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(onlyZenUnitPrintableUserType);
      //
      ARE_EQUAL("OnlyZenUnitPrintableUserType", toStringResult);

      ostringstream oss;
      ZenUnit::Printer<OnlyZenUnitPrintableUserType>::Print(oss, onlyZenUnitPrintableUserType);
      const string expectedZenUnitPrinterResult = oss.str();
      ARE_EQUAL(expectedZenUnitPrinterResult, toStringResult);
      ARE_EQUAL("OnlyZenUnitPrintableUserType", expectedZenUnitPrinterResult);
   }

   TEST(ToString_TypeHasZenUnitPrinter_TypeHasOStreamInsertionOperator_ReturnsZenUnitPrinterResult)
   {
      const DoublyPrintableUserType doublyPrintableUserType{};
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(doublyPrintableUserType);
      //
      ARE_EQUAL("DoublyPrintableUserType", toStringResult);

      ostringstream oss;
      ZenUnit::Printer<DoublyPrintableUserType>::Print(oss, doublyPrintableUserType);
      const string expectedZenUnitPrinterResult = oss.str();
      ARE_EQUAL(expectedZenUnitPrinterResult, toStringResult);
      ARE_EQUAL("DoublyPrintableUserType", expectedZenUnitPrinterResult);
   }

   TEST(ToStringConcat_ReturnsCommaSeparatedToStringedValues)
   {
      ARE_EQUAL("1", ToStringer::ToStringConcat(1));
      ARE_EQUAL("1, 2", ToStringer::ToStringConcat(1, 2));
      ARE_EQUAL("1, \"2\", 3", ToStringer::ToStringConcat(1, "2", 3));
      ARE_EQUAL("UserType@1, <NonPrintableUserType>, OnlyZenUnitPrintableUserType", ToStringer::ToStringConcat(
         UserType(1), NonPrintableUserType(), OnlyZenUnitPrintableUserType()));
   }

   RUN_TESTS(ToStringerTests)
}
