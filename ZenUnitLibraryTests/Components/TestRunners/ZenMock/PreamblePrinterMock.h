#pragma once

class PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
public:
   ZENMOCK_NONVOID2_CONST(string, PrintPreambleLinesAndGetStartTime, const ZenUnitArgs&, const TestClassRunnerRunner*)
};
