#pragma once
#include <vector>
#include <string>

class Program
{
public:
   int Main(int argc, char* argv[]) const;
   int ArgsMain(const std::vector<std::string>& args) const;
private:
   static std::vector<std::string> ArgcArgvToStringVector(int argc, char* argv[]);
};
