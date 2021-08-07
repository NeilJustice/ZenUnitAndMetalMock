#pragma once

class PreamblePrinterMock : public Metal::Mock<PreamblePrinter>
{
public:
   METALMOCK_NONVOID3_CONST(string, PrintPreambleLinesAndGetStartDateTime, const ZenUnitArgs&, size_t, const TestClassRunnerRunner*)
};
