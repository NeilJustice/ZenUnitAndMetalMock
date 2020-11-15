#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(FilePathLineNumberEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomFilePathLineNumber_ReturnsFilePathLineNumberWithAllRandomFields)
   AFACT(ZenUnitRandomFilePathLineNumber_DoesNotThrowException)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(FilePathLineNumber);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumber, filePath, ZenUnit::Random<const char*>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumber, lineNumber, ZenUnit::Random<unsigned>());
   }

   TEST(TestableRandomFilePathLineNumber_ReturnsFilePathLineNumberWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const char* const filePath = randomGeneratorMock.ConstCharPointerMock.ReturnRandom();
      const unsigned lineNumber = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
      //
      const FilePathLineNumber randomFilePathLineNumber = TestableRandomFilePathLineNumber(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.ConstCharPointerMock.CalledOnce());
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      FilePathLineNumber expectedRandomFilePathLineNumber;
      expectedRandomFilePathLineNumber.filePath = filePath;
      expectedRandomFilePathLineNumber.lineNumber = lineNumber;
      ARE_EQUAL(expectedRandomFilePathLineNumber, randomFilePathLineNumber);
   }

   TEST(ZenUnitRandomFilePathLineNumber_DoesNotThrowException)
   {
      const FilePathLineNumber randomFilePathLineNumber = ZenUnit::Random<FilePathLineNumber>();
   }

   RUN_TESTS(FilePathLineNumberEqualizerAndRandomTests)
}
