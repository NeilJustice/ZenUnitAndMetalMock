#pragma once
#include "ProgramArgs.h"

class ArgsParser
{
public:
   virtual ProgramArgs Parse(const std::vector<std::string>& args) const;
   virtual ~ArgsParser() = default;
};
