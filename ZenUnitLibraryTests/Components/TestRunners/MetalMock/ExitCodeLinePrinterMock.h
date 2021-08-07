#pragma once

class ExitCodeLinePrinterMock : public Metal::Mock<ExitCodeLinePrinter>
{
public:
   METALMOCK_VOID2_CONST(PrintExitCodeLine, int, bool)
};
