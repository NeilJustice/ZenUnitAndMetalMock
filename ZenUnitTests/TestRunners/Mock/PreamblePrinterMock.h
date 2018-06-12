#pragma once

struct PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
   ZENMOCK_NONVOID2_CONST(string, PrintOpeningThreeLinesAndGetStartTime, const ZenUnitArgs&, const TestClassRunnerRunner*)
};
