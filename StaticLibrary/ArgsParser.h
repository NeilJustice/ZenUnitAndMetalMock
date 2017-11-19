#pragma once
#include "ProgramArgs.h"

class ArgsParser
{
public:
   virtual ProgramArgs ParseArgs(const std::vector<std::string>& args) const;
   virtual ~ArgsParser();
};
