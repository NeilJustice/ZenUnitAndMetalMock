#include "pch.h"
#include "ZenUnit/Utils/Random.h"

TESTS(RandomTests)
FACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
FACT(Random_Float_ReturnsRandomFloat)
FACT(Random_Double_ReturnsRandomDouble)
FACT(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
FACT(Random_2ArgOverload_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
EVIDENCE

TEST(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
{
   Random<char>();
   Random<unsigned char>();
   Random<short>();
   Random<unsigned short>();
   Random<int>();
   Random<unsigned int>();
   Random<long long>();
   Random<unsigned long long>();
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

TEST(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
{
   string randomString = Random<string>();
   IS_TRUE(randomString.find("RandomString") != string::npos);
}

TEST(Random_2ArgOverload_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
{
   int randomInt = Random<int>(1, 3);
   IS_TRUE(randomInt >= 1 && randomInt <= 3, "randomInt = " + to_string(randomInt));

   enum Enum
   {
      A,
      B,
      C
   };
   Enum randomEnum = Random<Enum>(Enum::A, Enum::C);
   IS_TRUE(randomEnum >= Enum::A && randomEnum <= Enum::C, "randomEnum = " + to_string(randomEnum));
}

}; RUNTESTS(RandomTests)
