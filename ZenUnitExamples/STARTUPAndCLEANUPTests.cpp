#include "pch.h"

TESTS(STARTUPAndCLEANUPTests)
FACTS(Negate_ReturnsTrueIfFalse_ReturnsFalseIfTrue)
EVIDENCE

STARTUP
{
   std::cout << "First STARTUP";
}

CLEANUP
{
   std::cout << " then CLEANUP ";
}

static bool Negate(bool b)
{
   return !b;
}

TEST2X2(Negate_ReturnsTrueIfFalse_ReturnsFalseIfTrue,
   bool arg, bool expectedReturnValue,
   false, true,
   true, false)
{
   ARE_EQUAL(expectedReturnValue, Negate(arg));
}

RUN_TESTS(STARTUPAndCLEANUPTests)
