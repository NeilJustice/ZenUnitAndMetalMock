#pragma once
#include <string>
#include <vector>

class Program
{
public:
   int Main(int argc, char* argv[]) const;
   int Main(const std::vector<std::string>& args) const;
};
