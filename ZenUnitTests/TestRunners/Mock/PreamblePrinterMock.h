#pragma once

struct PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
   ZENMOCK_NONVOID2_CONST(string, PrintPreambleAndGetStartTime, const ZenUnitArgs&, const TestClassRunnerRunner*)
};
