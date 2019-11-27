#include "pch.h"

TESTS(RandomGeneratorTests)
AFACT(AllFunctions_CodeCoverage)
EVIDENCE

RandomGenerator _randomGenerator;

TEST(AllFunctions_CodeCoverage)
{
   _randomGenerator.Char();
   _randomGenerator.UnsignedChar();
   _randomGenerator.Bool();
   _randomGenerator.Short();
   _randomGenerator.UnsignedShort();
   _randomGenerator.Int();
   _randomGenerator.UnsignedInt();
   _randomGenerator.Enum(0);
   _randomGenerator.LongLong();
   _randomGenerator.UnsignedLongLong();
   _randomGenerator.SizeT();
   _randomGenerator.Float();
   _randomGenerator.Double();
   _randomGenerator.ConstCharPointer();
   _randomGenerator.String();
   _randomGenerator.StringVector();
   _randomGenerator.Path();
   _randomGenerator.ErrorCode();
}

RUN_TESTS(RandomGeneratorTests)
