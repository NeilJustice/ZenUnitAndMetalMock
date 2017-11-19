#pragma once
#include <string>

class Console
{
public:
   virtual void WriteLine(const std::string& message) const;
   virtual void WriteNewline() const;
   virtual ~Console();
};
