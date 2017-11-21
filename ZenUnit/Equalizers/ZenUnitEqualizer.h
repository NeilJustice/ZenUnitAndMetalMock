#pragma once
#include "ZenUnit/Anomaly/EqualizerException.h"
#include <string>

namespace ZenUnit
{
   template<typename ExpectedAndActualType>
   struct Equalizer
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
   struct TwoTypeEqualizer
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
   struct Equalizer<const char*>
   {
      static void AssertEqual(const char* expected, const char* actual);
   };
   template<>
   struct Equalizer<char*>
   {
      static void AssertEqual(char* expected, char* actual);
   };

   template<>
   struct TwoTypeEqualizer<const char*, char*>
   {
      static void AssertEqual(const char* expected, char* actual);
   };
   template<>
   struct TwoTypeEqualizer<char*, const char*>
   {
      static void AssertEqual(char* expected, const char* actual);
   };

   template<>
   struct TwoTypeEqualizer<const char*, std::string>
   {
      static void AssertEqual(const char* expected, const std::string& actual);
   };
   template<>
   struct TwoTypeEqualizer<std::string, const char*>
   {
      static void AssertEqual(const std::string& expected, const char* actual);
   };

   template<>
   struct TwoTypeEqualizer<char*, std::string>
   {
      static void AssertEqual(char* expected, const std::string& actual);
   };
   template<>
   struct TwoTypeEqualizer<std::string, char*>
   {
      static void AssertEqual(const std::string& expected, char* actual);
   };

   template<>
   struct Equalizer<double>
   {
      static void AssertEqual(double expected, double actual);
   };

   template<>
   struct Equalizer<float>
   {
      static void AssertEqual(float expected, float actual);
   };

   template<>
   struct TwoTypeEqualizer<int, unsigned>
   {
      static void AssertEqual(int expected, unsigned actual);
   };

#if defined(__linux__) || defined(_WIN64)

   template<>
   struct TwoTypeEqualizer<int, size_t>
   {
      static void AssertEqual(int expected, size_t actual);
   };
}

#endif
