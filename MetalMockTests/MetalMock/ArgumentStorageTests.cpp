#include "pch.h"

TESTS(MutableCharSpanArgumentStorageTests)
AFACT(DefaultConstructor_SetsValueToEmptyString)
AFACT(OneArgConstructor_CopiesCharSpanToStringValue)
EVIDENCE

TEST(DefaultConstructor_SetsValueToEmptyString)
{
   MetalMock::ArgumentStorage<std::span<char>> argumentStorage;
   IS_EMPTY_STRING(argumentStorage.value);
}

TEST(OneArgConstructor_CopiesCharSpanToStringValue)
{
   string str = ZenUnit::Random<string>();
   span<char> charSpan(str);
   //
   MetalMock::ArgumentStorage<std::span<char>> argumentStorage(charSpan);
   //
   ARE_EQUAL(str, argumentStorage.value);
}

RUN_TESTS(MutableCharSpanArgumentStorageTests)


TESTS(ConstantCharSpanArgumentStorageTests)
AFACT(DefaultConstructor_SetsValueToEmptyString)
AFACT(OneArgConstructor_CopiesCharSpanToStringValue)
EVIDENCE

TEST(DefaultConstructor_SetsValueToEmptyString)
{
   MetalMock::ArgumentStorage<std::span<const char>> argumentStorage;
   IS_EMPTY_STRING(argumentStorage.value);
}

TEST(OneArgConstructor_CopiesCharSpanToStringValue)
{
   const string str = ZenUnit::Random<string>();
   span<const char> charSpan(str);
   //
   MetalMock::ArgumentStorage<std::span<const char>> argumentStorage(charSpan);
   //
   ARE_EQUAL(str, argumentStorage.value);
}

RUN_TESTS(ConstantCharSpanArgumentStorageTests)
