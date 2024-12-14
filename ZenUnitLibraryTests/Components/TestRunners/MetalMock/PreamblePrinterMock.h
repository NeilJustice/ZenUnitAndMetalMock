#pragma once

class PreamblePrinterMock : public Metal::Mock<PreamblePrinter>
{
public:
   METALMOCK_VOID3_CONST(PrintPreambleLines, const ZenUnitArgs&, size_t, const TestClassRunnerRunner*)
};
