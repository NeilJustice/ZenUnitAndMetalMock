#pragma once
#include <memory>
#include <string>
#include <vector>
class Console;
class ArgsParser;
struct ProgramArgs;

class Program
{
private:
   std::unique_ptr<const Console> _console;
   std::unique_ptr<const ArgsParser> _argsParser;
public:
   Program();
   ~Program();
   int Main(int argc, char* argv[]) const;
   int VectorMain(const std::vector<std::string>& args) const;
   int ArgsMain(const ProgramArgs& programArgs) const;
};
