#include "pch.h"
#include "Console.h"

void Console::WriteLine(const std::string& message) const
{
   printf(message.c_str());
   printf("\n");
}

void Console::WriteNewline() const
{
   printf("\n");
}

Console::~Console()
{
}
