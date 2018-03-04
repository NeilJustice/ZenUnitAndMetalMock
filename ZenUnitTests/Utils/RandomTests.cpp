#include "pch.h"

TESTS(RandomTests)
AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
AFACT(Random_Float_ReturnsRandomFloat)
AFACT(Random_Double_ReturnsRandomDouble)
AFACT(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
AFACT(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
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
   const string randomString = Random<string>();
   IS_TRUE(randomString.find("RandomString") != string::npos);
}

TEST(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
{
   const int randomInt = RandomBetween<int>(1, 3);
   IS_TRUE(randomInt >= 1 && randomInt <= 3, "randomInt = " + to_string(randomInt));

   enum Enum
   {
      A,
      B,
      C
   };
   const Enum randomEnum = RandomBetween<Enum>(Enum::A, Enum::C);
   IS_TRUE(randomEnum >= Enum::A && randomEnum <= Enum::C, "randomEnum = " + to_string(randomEnum));
}

RUN_TESTS(RandomTests)


template<typename T>
TEMPLATE_TESTS(RandomVectorTests, T)
AFACT(RandomVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
EVIDENCE

TEST(RandomVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
{
   const vector<T> randomVector = ZenUnit::RandomVector<T>();
   IS_TRUE(randomVector.size() >= 0 && randomVector.size() <= 2);
}

RUN_TEMPLATE_TESTS(RandomVectorTests, int)
THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)
