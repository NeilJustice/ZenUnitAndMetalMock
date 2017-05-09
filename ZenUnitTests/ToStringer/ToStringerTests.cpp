#include "pch.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnitTests/Testing/UserTypeInsOpAndZenUnitPrintable.h"
#include "ZenUnitTests/Testing/UserTypeOnlyZenUnitPrintable.h"

struct ToStringerTestStruct
{
   int value;

   ToStringerTestStruct(int value)
      : value(value)
      , argValue(0)
      , numberOfCalls(0)
   {
   }

   mutable int argValue;
   mutable size_t numberOfCalls;

   friend ostream& operator<<(ostream& os, const ToStringerTestStruct& sts)
   {
      ++sts.numberOfCalls;
      sts.argValue = sts.value;
      return os;
   }

   void AssertInsertionOperatorCalledOnceWith(int expectedValue)
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedValue, argValue);
   }
};

enum Enum { E0, E1 };
enum class EnumClass : long long
{
   EC0,
   EC1 = static_cast<long long>(numeric_limits<int>::max()) + 1
};

namespace ZenUnit
{
   TESTS(ToStringerTests)
   SPEC(ToString_Arithmetic_ReturnsResultOfStdToString)
   SPEC(ToString_Enum_ReturnsStdToStringOnTheValue)
   SPEC(ToString_EnumClass_ReturnsStdToStringOnTheValue)
   SPEC(ToString_Nullptr_ReturnsNullptrInBrackets)
   SPEC(ToString_NonArithmeticType_ReturnsInsertionOperatorValue)
   SPEC(ToString_Pointer_ReturnsNullptrIfNullptrOtherwiseMemoryAddress)
   SPEC(ToString_UniquePtr_ReturnsPointeeAddress)
   SPEC(ToString_UniquePtrWithCustomDeleter_ReturnsPointeeAddress)
   SPEC(ToString_SharedPtr_ReturnsPointeeAddress)
   SPECX(ToString_VoidZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction)
   SPECX(ToString_NonVoidNonZeroArgStdFunction_ReturnsEmptyOrNonEmptyStdFunction)
   SPEC(ToString_CharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   SPEC(ToString_ConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   SPEC(ToString_Char_ReturnsQuotedChar)
   SPEC(ToString_Bool_ReturnsBoolAlpha)
   SPEC(ToString_Pair_ReturnsLeftParenFirstValueCommaSecondValueRightParen)
   SPEC(ToString_TypeHasNeitherOStreamInsertionOperatorOrZenUnitPrint_ReturnsRTTINameInBrackets)
   SPEC(ToString_TypeHasOStreamInsertionOperatorAndNotZenUnitPrint_ReturnsOStreamLeftShiftResult)
   SPEC(ToString_TypeDoesNotHaveOStreamInsertionOperatorAndHasZenUnitPrint_ReturnsQuotedZenUnitPrintResult)
   SPEC(ToString_TypeHasOStreamInsertionOperatorAndZenUnitPrint_ReturnsQuotedZenUnitPrintResult)
   SPEC(ToStringConcat_ReturnsCommaSeparatedToStringedValues)
   SPECEND

   TEST(ToString_Arithmetic_ReturnsResultOfStdToString)
   {
      ARE_EQUAL("-1", ToStringer::ToString(-1));
      ARE_EQUAL("0", ToStringer::ToString(0));
      ARE_EQUAL("1", ToStringer::ToString(1));

      ARE_EQUAL("-1.123457", ToStringer::ToString(-1.1234567f));
      ARE_EQUAL("0.000000", ToStringer::ToString(0.0f));
      ARE_EQUAL("1.100000", ToStringer::ToString(1.1f));
      ARE_EQUAL("1.123457", ToStringer::ToString(1.1234567f));

      ARE_EQUAL("-1.123457", ToStringer::ToString(-1.1234567));
      ARE_EQUAL("0.000000", ToStringer::ToString(0.0));
      ARE_EQUAL("1.100000", ToStringer::ToString(1.1));
      ARE_EQUAL("1.123457", ToStringer::ToString(1.1234567));
   }

   TEST(ToString_Enum_ReturnsStdToStringOnTheValue)
   {
      ARE_EQUAL("0", ToStringer::ToString(Enum::E0));
      ARE_EQUAL("1", ToStringer::ToString(Enum::E1));
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
      std::nullptr_t nullPointerType;
      ARE_EQUAL("nullptr", ToStringer::ToString(nullPointerType));
      ARE_EQUAL("nullptr", ToStringer::ToString(nullptr));
   }

   TEST(ToString_NonArithmeticType_ReturnsInsertionOperatorValue)
   {
      ToStringerTestStruct s(1);
      //
      ToStringer::ToString(s);
      //
      s.AssertInsertionOperatorCalledOnceWith(1);
   }

   TEST(ToString_Pointer_ReturnsNullptrIfNullptrOtherwiseMemoryAddress)
   {
      const int* const intPointerNullptr = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(intPointerNullptr));

      const int* const constIntPointerNullptr = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(constIntPointerNullptr));

      const int* const constIntPointerNullptrConst = nullptr;
      ARE_EQUAL("nullptr", ToStringer::ToString(constIntPointerNullptrConst));

   #ifdef __linux__
      int* intPointer1 = reinterpret_cast<int*>(0x1);
      ARE_EQUAL("0x1", ToStringer::ToString(intPointer1));
      int* intPointerFF = reinterpret_cast<int*>(0xFF);
      ARE_EQUAL("0xff", ToStringer::ToString(intPointerFF));
      int* intPointerMaxAsHex = reinterpret_cast<int*>(0xFFFFFFFFFFFFFFFF);
      ARE_EQUAL("0xffffffffffffffff", ToStringer::ToString(intPointerMaxAsHex));
      int* intPointerMaxAsBinary = reinterpret_cast<int*>(0b1111111111111111111111111111111111111111111111111111111111111111);
      ARE_EQUAL("0xffffffffffffffff", ToStringer::ToString(intPointerMaxAsBinary));
   #elif _WIN32
      const int* const intPointer1 = reinterpret_cast<const int*>(0x1);
      ARE_EQUAL("0x0000000000000001", ToStringer::ToString(intPointer1));
      const int* const intPointerFF = reinterpret_cast<const int*>(0xFF);
      ARE_EQUAL("0x00000000000000FF", ToStringer::ToString(intPointerFF));
      const int* const intPointerMaxAsHex = reinterpret_cast<const int*>(0xFFFFFFFFFFFFFFFF);
      ARE_EQUAL("0xFFFFFFFFFFFFFFFF", ToStringer::ToString(intPointerMaxAsHex));
      const int* intPointerMaxAsBinary = reinterpret_cast<const int*>(0b1111111111111111111111111111111111111111111111111111111111111111);
      ARE_EQUAL("0xFFFFFFFFFFFFFFFF", ToStringer::ToString(intPointerMaxAsBinary));
   #endif
      const int* intPointerMid = reinterpret_cast<const int*>(0x1111111111111111);
      ARE_EQUAL("0x1111111111111111", ToStringer::ToString(intPointerMid));
   }

   TEST(ToString_UniquePtr_ReturnsPointeeAddress)
   {
      const unique_ptr<int> nullUniquePtr(nullptr);
      ARE_EQUAL("nullptr", ToStringer::ToString(nullUniquePtr));

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
   #ifdef __linux__
      return R"(0x\w+)";
   #elif _WIN32
      return R"(0x\w\w\w\w\w\w\w\w\w\w\w\w\w\w\w\w)";
   #endif
   }

   TEST(ToString_SharedPtr_ReturnsPointeeAddress)
   {
      const shared_ptr<const int> nullSharedPtr(nullptr);
      ARE_EQUAL("nullptr", ToStringer::ToString(nullSharedPtr));

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
      std::function<void()> stdFunction;
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
      std::function<int(char, float, double)> stdFunction;
      if (!stdFunctionIsEmpty)
      {
         stdFunction = [](char, float, double) { return 0; };
         stdFunction('a', 10.0f, 20.0); // Lambda code coverage
      }
      ARE_EQUAL(expectedReturnValue, ToStringer::ToString(stdFunction));
   }

   TEST(ToString_CharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      ARE_EQUAL("nullptr", ToStringer::ToString(static_cast<char*>(nullptr)));
      const char chars[] { 0 };
      ARE_EQUAL("\"\"", ToStringer::ToString(chars));
      const char charsABC[] { 'A', 'B', 'C', 0 };
      ARE_EQUAL("\"ABC\"", ToStringer::ToString(charsABC));
   }

   TEST(ToString_ConstCharPointer_ReturnsNullptrIfNullptrOtherwiseQuotedString)
   {
      ARE_EQUAL("nullptr", ToStringer::ToString(static_cast<const char*>(nullptr)));
      ARE_EQUAL("\"\"", ToStringer::ToString(""));
      ARE_EQUAL("\"ABC\"", ToStringer::ToString("ABC"));
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
   #ifdef __linux__
      ARE_EQUAL("(0x1, 5)", ToStringer::ToString(pair<int*, int>(reinterpret_cast<int*>(0x1), 5)));
   #elif _WIN32
      ARE_EQUAL("(0x0000000000000001, 5)", ToStringer::ToString(pair<int*, int>(reinterpret_cast<int*>(0x1), 5)));
   #endif
   }

   TEST(ToString_TypeHasNeitherOStreamInsertionOperatorOrZenUnitPrint_ReturnsRTTINameInBrackets)
   {
      const UserTypeNonPrintable userTypeNonPrintable;
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(userTypeNonPrintable);
      //
      ARE_EQUAL("<UserTypeNonPrintable>", toStringResult);
   }

   TEST(ToString_TypeHasOStreamInsertionOperatorAndNotZenUnitPrint_ReturnsOStreamLeftShiftResult)
   {
      const UserType userType(1);
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(userType);
      //
      ARE_EQUAL("UserType@1", toStringResult);
   }

   TEST(ToString_TypeDoesNotHaveOStreamInsertionOperatorAndHasZenUnitPrint_ReturnsQuotedZenUnitPrintResult)
   {
      const UserTypeOnlyZenUnitPrintable zenUnitPrintOnly{};
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(zenUnitPrintOnly);
      //
      ostringstream oss;
      ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>::Print(oss, zenUnitPrintOnly);
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(zenUnitPrintResult, toStringResult);
      ARE_EQUAL("UserTypeOnlyZenUnitPrintable", toStringResult);
   }

   TEST(ToString_TypeHasOStreamInsertionOperatorAndZenUnitPrint_ReturnsQuotedZenUnitPrintResult)
   {
      const UserTypeInsOpAndZenUnitPrintable userTypeInsOpAndZenUnitPrintable{};
      //
      const string toStringResult = ZenUnit::ToStringer::ToString(userTypeInsOpAndZenUnitPrintable);
      //
      ostringstream oss;
      ZenUnitPrinter<UserTypeInsOpAndZenUnitPrintable>::Print(oss, userTypeInsOpAndZenUnitPrintable);
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(zenUnitPrintResult, toStringResult);
      ARE_EQUAL("UserTypeInsOpAndZenUnitPrintable", toStringResult);
   }

   TEST(ToStringConcat_ReturnsCommaSeparatedToStringedValues)
   {
      ARE_EQUAL("1", ToStringer::ToStringConcat(1));
      ARE_EQUAL("1, 2", ToStringer::ToStringConcat(1, 2));
      ARE_EQUAL("1, \"2\", 3", ToStringer::ToStringConcat(1, "2", 3));
      ARE_EQUAL("UserType@1, <UserTypeNonPrintable>, UserTypeOnlyZenUnitPrintable", ToStringer::ToStringConcat(
         UserType(1), UserTypeNonPrintable(), UserTypeOnlyZenUnitPrintable()));
   }

   }; RUN(ToStringerTests)
}
