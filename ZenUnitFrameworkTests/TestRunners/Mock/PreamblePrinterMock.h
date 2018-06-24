#pragma once

class PreamblePrinterMock : public Zen::Mock<PreamblePrinter>
{
public:
   ZENMOCK_NONVOID2_CONST(string, PrintPreambleAndGetStartTime, const ZenUnitArgs&, const TestClassRunnerRunner*)
};
