#include "pch.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   INLINE void Equalizer<const char*>::
   AssertEqual(const char* expected, const char* actual)
   {
      if (expected == nullptr && actual == nullptr)
      {
         return;
      }
      if (expected == nullptr && actual != nullptr)
      {
         throw EqualizerException();
      }
      if (expected != nullptr && actual == nullptr)
      {
         throw EqualizerException();
      }
      int strcmpResult = strcmp(expected, actual);
      if (strcmpResult != 0)
      {
         throw EqualizerException();
      }
   }

   INLINE void Equalizer<char*>::
   AssertEqual(char* expected, char* actual)
   {
      Equalizer<const char*>::AssertEqual(expected, actual);
   }

   INLINE void TwoTypeEqualizer<const char*, char*>::
   AssertEqual(const char* expected, char* actual)
   {
      Equalizer<const char*>::AssertEqual(expected, actual);
   }

   INLINE void TwoTypeEqualizer<char*, const char*>::
   AssertEqual(char* expected, const char* actual)
   {
      Equalizer<const char*>::AssertEqual(expected, actual);
   }

   INLINE void TwoTypeEqualizer<const char*, std::string>::
   AssertEqual(const char* expected, const std::string& actual)
   {
      Equalizer<const char*>::AssertEqual(expected, actual.c_str());
   }

   INLINE void TwoTypeEqualizer<std::string, const char*>::
   AssertEqual(const std::string& expected, const char* actual)
   {
      Equalizer<const char*>::AssertEqual(expected.c_str(), actual);
   }

   INLINE void Equalizer<double>::
   AssertEqual(double expected, double actual)
   {
      // Tentative exactly-equal implementation
      if (!(expected == actual))
      {
         throw EqualizerException();
      }
   }

   INLINE void Equalizer<float>::
   AssertEqual(float expected, float actual)
   {
      // Tentative exactly-equal implementation
      if (!(expected == actual))
      {
         throw EqualizerException();
      }
   }

   INLINE void TwoTypeEqualizer<int, unsigned>::
   AssertEqual(int expected, unsigned actual)
   {
      if (expected < 0)
      {
         throw EqualizerException();
      }
      Equalizer<unsigned>::AssertEqual(static_cast<unsigned>(expected), actual);
   }

#if defined(__linux__) || defined(_WIN64)

   INLINE void TwoTypeEqualizer<int, size_t>::
   AssertEqual(int expected, size_t actual)
   {
      if (expected < 0)
      {
         throw EqualizerException();
      }
      Equalizer<size_t>::AssertEqual(static_cast<size_t>(expected), actual);
   }
#endif
}
