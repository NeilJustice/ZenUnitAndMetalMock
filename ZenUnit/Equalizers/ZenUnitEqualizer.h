#pragma once
#include "ZenUnit/Anomaly/EqualizerException.h"

template<typename ExpectedAndActualType>
struct ZenUnitEqualizer
{
   static void AssertEqual(
      const ExpectedAndActualType& expected, const ExpectedAndActualType& actual)
   {
      if (!(expected == actual))
      {
         throw ZenUnit::EqualizerException();
      }
   }
};

template<typename ExpectedType, typename ActualType>
struct TwoTypeZenUnitEqualizer
{
   static void AssertEqual(const ExpectedType& expected, const ActualType& actual)
   {
      if (!(expected == actual))
      {
         throw ZenUnit::EqualizerException();
      }
   }
};

template<>
struct ZenUnitEqualizer<const char*>
{
   static void AssertEqual(const char* expected, const char* actual);
};
template<>
struct ZenUnitEqualizer<char*>
{
   static void AssertEqual(char* expected, char* actual);
};

template<>
struct TwoTypeZenUnitEqualizer<const char*, char*>
{
   static void AssertEqual(const char* expected, char* actual);
};
template<>
struct TwoTypeZenUnitEqualizer<char*, const char*>
{
   static void AssertEqual(char* expected, const char* actual);
};

template<>
struct TwoTypeZenUnitEqualizer<const char*, std::string>
{
   static void AssertEqual(const char* expected, const std::string& actual);
};
template<>
struct TwoTypeZenUnitEqualizer<std::string, const char*>
{
   static void AssertEqual(const std::string& expected, const char* actual);
};

template<>
struct TwoTypeZenUnitEqualizer<char*, std::string>
{
   static void AssertEqual(char* expected, const std::string& actual);
};
template<>
struct TwoTypeZenUnitEqualizer<std::string, char*>
{
   static void AssertEqual(const std::string& expected, char* actual);
};

template<>
struct ZenUnitEqualizer<double>
{
   static void AssertEqual(double expected, double actual);
};

template<>
struct ZenUnitEqualizer<float>
{
   static void AssertEqual(float expected, float actual);
};

template<>
struct TwoTypeZenUnitEqualizer<int, unsigned>
{
   static void AssertEqual(int expected, unsigned actual);
};

template<>
struct TwoTypeZenUnitEqualizer<int, size_t>
{
   static void AssertEqual(int expected, size_t actual);
};
