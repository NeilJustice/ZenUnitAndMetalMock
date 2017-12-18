#include "pch.h"
#include "StaticLibrary/Console.h"

void Console::WriteLine(const std::string& message) const
{
   cout << message << '\n';
}

void Console::WriteNewline() const
{
   cout << '\n';
}

Console::~Console()
{
}