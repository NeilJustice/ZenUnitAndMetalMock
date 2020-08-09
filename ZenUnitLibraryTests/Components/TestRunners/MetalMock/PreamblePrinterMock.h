#pragma once

class PreamblePrinterMock : public Metal::Mock<PreamblePrinter>
{
public:
   METALMOCK_NONVOID2_CONST(string, PrintPreambleLinesAndGetStartDateTime, const ZenUnitArgs&, const TestClassRunnerRunner*)
};
