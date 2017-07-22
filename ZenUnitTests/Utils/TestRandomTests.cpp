#include "pch.h"
#include "ZenUnit/Utils/TestRandom.h"

TESTS(TestRandomTests)
SPEC(TestRandom_Int_ReturnsRandomInt)
SPEC(TestRandom_Unsigned_ReturnsRandomUnsigned)
SPEC(TestRandom_SizeT_ReturnsRandomSizeT)
SPEC(TestRandom_String_ReturnsRandomString)
SPECEND

TEST(TestRandom_Int_ReturnsRandomInt)
{
   TestRandom<int>();
}

TEST(TestRandom_Unsigned_ReturnsRandomUnsigned)
{
   TestRandom<unsigned>();
}

TEST(TestRandom_SizeT_ReturnsRandomSizeT)
{
   TestRandom<size_t>();
}

TEST(TestRandom_String_ReturnsRandomString)
{
   TestRandom<string>();
}

}; RUN(TestRandomTests)
