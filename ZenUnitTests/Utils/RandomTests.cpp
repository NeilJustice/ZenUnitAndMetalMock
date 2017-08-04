#include "pch.h"
#include "ZenUnit/Utils/Random.h"

TESTS(RandomTests)
SPEC(Random_Int_ReturnsRandomInt)
SPEC(Random_Unsigned_ReturnsRandomUnsigned)
SPEC(Random_Float_ReturnsRandomFloat)
SPEC(Random_Double_ReturnsRandomDouble)
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

TEST(Random_Float_ReturnsRandomFloat)
{
   Random<float>();
}

TEST(Random_Double_ReturnsRandomDouble)
{
   Random<double>();
}

TEST(Random_String_ReturnsRandomString)
{
   Random<string>();
}

}; RUN(RandomTests)
