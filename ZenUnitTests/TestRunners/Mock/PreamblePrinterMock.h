#pragma once

struct PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
   ZENMOCK_VOID2_CONST(PrintOpeningThreeLines, const ZenUnitArgs&, const MultiTestClassRunner*)
};
