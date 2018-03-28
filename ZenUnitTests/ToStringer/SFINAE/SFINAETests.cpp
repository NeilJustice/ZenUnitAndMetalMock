#include "pch.h"
#include "ZenUnitTests/Testing/UserType.h"
#include "ZenUnitTests/Testing/UserTypeInsOpAndZenUnitPrintable.h"
#include "ZenUnitTests/Testing/UserTypeNonPrintable.h"
#include "ZenUnitTests/Testing/UserTypeOnlyZenUnitPrintable.h"

namespace ZenUnit
{

TESTS(has_ostream_left_shiftTests)
AFACT(value_IsFalseIfFreeFunctionOStreamInsertionOperatorNotDefinedForType)
AFACT(value_IsTrueIfFreeFunctionOStreamInsertionOperatorIsDefinedForType)
EVIDENCE

TEST(value_IsFalseIfFreeFunctionOStreamInsertionOperatorNotDefinedForType)
{
   IS_FALSE(has_ostream_left_shift<vector<int>>::value);
   IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable>::value);

   IS_FALSE(has_ostream_left_shift<UserType>::value);
   IS_FALSE(has_ostream_left_shift<UserType&>::value);
   IS_FALSE(has_ostream_left_shift<const UserType&>::value);
   IS_FALSE(has_ostream_left_shift<UserType&&>::value);

   IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable>::value);
   IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable&>::value);
   IS_FALSE(has_ostream_left_shift<const UserTypeNonPrintable&>::value);
   IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable&&>::value);

   IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable>::value);
   IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable&>::value);
   IS_FALSE(has_ostream_left_shift<const UserTypeOnlyZenUnitPrintable&>::value);
   IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable&&>::value);
}

TEST(value_IsTrueIfFreeFunctionOStreamInsertionOperatorIsDefinedForType)
{
   IS_TRUE(has_ostream_left_shift<int>::value);
   IS_TRUE(has_ostream_left_shift<int*>::value);

   IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable>::value);
   IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable&>::value);
   IS_TRUE(has_ostream_left_shift<const UserTypeInsOpAndZenUnitPrintable&>::value);
   IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable&&>::value);
}

RUN_TESTS(has_ostream_left_shiftTests)


TESTS(has_to_stringTests)
AFACT(HasStdToString_ValueIsTrue)
AFACT(DoesNotHaveStdToSTring_ValueIsFalse)
EVIDENCE

TEST(HasStdToString_ValueIsTrue)
{
   IS_TRUE(has_to_string<char>::value);
   IS_TRUE(has_to_string<int>::value);
   IS_TRUE(has_to_string<long long>::value);
   IS_TRUE(has_to_string<unsigned long long>::value);
}

TEST(DoesNotHaveStdToSTring_ValueIsFalse)
{
   IS_FALSE(has_to_string<const char*>::value);
   IS_FALSE(has_to_string<string>::value);
   IS_FALSE(has_to_string<vector<string>>::value);
   IS_FALSE(has_to_string<UserType>::value);
}

RUN_TESTS(has_to_stringTests)


namespace Namespace
{
   struct StructInsideNamespace_ZenUnitPrintOutsideNamespace {};
}

struct NonConstReferenceZenUnitPrint {};
template<>
struct Printer<NonConstReferenceZenUnitPrint>
{
   static void Print(ostream&, NonConstReferenceZenUnitPrint&);
};

struct RValueReferenceZenUnitPrint {};
template<>
struct Printer<RValueReferenceZenUnitPrint>
{
   static void Print(ostream&, RValueReferenceZenUnitPrint&&);
};

template<>
struct Printer<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>
{
   static void Print(ostream&, const Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace&);
};

TESTS(has_ZenUnitPrinterTests)
AFACT(value_FalseIfZenUnitPrinterNotDefinedForType)
AFACT(value_TrueIfZenUnitPrinterIsDefinedForType)
EVIDENCE

TEST(value_FalseIfZenUnitPrinterNotDefinedForType)
{
   IS_FALSE(has_ZenUnitPrinter<int>::value);
   IS_FALSE(has_ZenUnitPrinter<string>::value);
   IS_FALSE(has_ZenUnitPrinter<UserTypeNonPrintable>::value);
   IS_FALSE(has_ZenUnitPrinter<NonConstReferenceZenUnitPrint>::value);
   IS_FALSE(has_ZenUnitPrinter<RValueReferenceZenUnitPrint>::value);
}

TEST(value_TrueIfZenUnitPrinterIsDefinedForType)
{
   IS_TRUE(has_ZenUnitPrinter<vector<int>>::value);
   IS_TRUE(has_ZenUnitPrinter<vector<string>>::value);

   IS_TRUE(has_ZenUnitPrinter<map<int Comma int>>::value);
   IS_TRUE(has_ZenUnitPrinter<unordered_map<int Comma int>>::value);
   IS_TRUE(has_ZenUnitPrinter<map<char Comma string>>::value);
   IS_TRUE(has_ZenUnitPrinter<unordered_map<char Comma string>>::value);

   IS_TRUE(has_ZenUnitPrinter<set<int>>::value);
   IS_TRUE(has_ZenUnitPrinter<unordered_set<int>>::value);
   IS_TRUE(has_ZenUnitPrinter<set<string>>::value);
   IS_TRUE(has_ZenUnitPrinter<unordered_set<string>>::value);

   IS_TRUE(has_ZenUnitPrinter<UserType>::value);
   IS_TRUE(has_ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>::value);
   IS_TRUE(has_ZenUnitPrinter<UserTypeInsOpAndZenUnitPrintable>::value);
   IS_TRUE(has_ZenUnitPrinter<Namespace::StructInsideNamespace_ZenUnitPrintOutsideNamespace>::value);
}

RUN_TESTS(has_ZenUnitPrinterTests)

static_assert(is_quoted_when_printed<char*>::value);
static_assert(is_quoted_when_printed<char* const>::value);
static_assert(is_quoted_when_printed<const char*>::value);
static_assert(is_quoted_when_printed<const char* const>::value);
static_assert(is_quoted_when_printed<string>::value);
static_assert(is_quoted_when_printed<string&>::value);
static_assert(is_quoted_when_printed<const string>::value);
static_assert(is_quoted_when_printed<const string&>::value);

static_assert(is_quoted_when_printed<char[1]>::value);
static_assert(is_quoted_when_printed<const char[1]>::value);

static_assert(!is_quoted_when_printed<int>::value);
static_assert(!is_quoted_when_printed<char>::value);
static_assert(!is_quoted_when_printed<exception>::value);
static_assert(!is_quoted_when_printed<UserType>::value);
static_assert(!is_quoted_when_printed<UserTypeNonPrintable>::value);

}