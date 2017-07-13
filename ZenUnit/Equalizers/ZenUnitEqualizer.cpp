#include "pch.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

void ZenUnitEqualizer<const char*>::
AssertEqual(const char* expected, const char* actual)
{
   if (expected == nullptr && actual == nullptr)
   {
      return;
   }
   if (expected == nullptr && actual != nullptr)
   {
      throw ZenUnit::EqualizerException();
   }
   if (expected != nullptr && actual == nullptr)
   {
      throw ZenUnit::EqualizerException();
   }
   int strcmpResult = strcmp(expected, actual);
   if (strcmpResult != 0)
   {
      throw ZenUnit::EqualizerException();
   }
}

void ZenUnitEqualizer<char*>::
AssertEqual(char* expected, char* actual)
{
   ZenUnitEqualizer<const char*>::AssertEqual(expected, actual);
}

void TwoTypeZenUnitEqualizer<const char*, char*>::
AssertEqual(const char* expected, char* actual)
{
   ZenUnitEqualizer<const char*>::AssertEqual(expected, actual);
}

void TwoTypeZenUnitEqualizer<char*, const char*>::
AssertEqual(char* expected, const char* actual)
{
   ZenUnitEqualizer<const char*>::AssertEqual(expected, actual);
}

void TwoTypeZenUnitEqualizer<const char*, string>::
AssertEqual(const char* expected, const string& actual)
{
   ZenUnitEqualizer<const char*>::AssertEqual(expected, actual.c_str());
}

void TwoTypeZenUnitEqualizer<string, const char*>::
AssertEqual(const string& expected, const char* actual)
{
   ZenUnitEqualizer<const char*>::AssertEqual(expected.c_str(), actual);
}

void ZenUnitEqualizer<double>::
AssertEqual(double expected, double actual)
{
   // Tentative exactly-equal implementation
   if (!(expected == actual))
   {
      throw ZenUnit::EqualizerException();
   }
}

void ZenUnitEqualizer<float>::
AssertEqual(float expected, float actual)
{
   // Tentative exactly-equal implementation
   if (!(expected == actual))
   {
      throw ZenUnit::EqualizerException();
   }
}

void TwoTypeZenUnitEqualizer<int, unsigned>::
AssertEqual(int expected, unsigned actual)
{
   if (expected < 0)
   {
      throw ZenUnit::EqualizerException();
   }
   ZenUnitEqualizer<unsigned>::AssertEqual(static_cast<unsigned>(expected), actual);
}

#if defined(__linux__) || defined(_WIN64)

void TwoTypeZenUnitEqualizer<int, size_t>::
AssertEqual(int expected, size_t actual)
{
   if (expected < 0)
   {
      throw ZenUnit::EqualizerException();
   }
   ZenUnitEqualizer<size_t>::AssertEqual(static_cast<size_t>(expected), actual);
}

#endif