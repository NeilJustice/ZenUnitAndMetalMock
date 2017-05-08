#pragma once
#include "ZenUnit/TestRunners/PreamblePrinter.h"

struct PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
   ZENMOCK_VOID2_CONST(PrintOpeningThreeLines, const string&, const MultiTestClassRunner*)
};
