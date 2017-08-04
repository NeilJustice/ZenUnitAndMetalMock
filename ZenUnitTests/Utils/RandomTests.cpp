#include "pch.h"
#include "ZenUnit/Utils/Random.h"

TESTS(RandomTests)
SPEC(Random_Int_ReturnsRandomInt)
SPEC(Random_Unsigned_ReturnsRandomUnsigned)
SPEC(Random_SizeT_ReturnsRandomSizeT)
SPEC(Random_String_ReturnsRandomString)
SPECEND

TEST(Random_Int_ReturnsRandomInt)
{
   Random<int>();
}

TEST(Random_Unsigned_ReturnsRandomUnsigned)
{
   Random<unsigned>();
}

TEST(Random_SizeT_ReturnsRandomSizeT)
{
   Random<size_t>();
}

TEST(Random_String_ReturnsRandomString)
{
   Random<string>();
}

}; RUN(RandomTests)
