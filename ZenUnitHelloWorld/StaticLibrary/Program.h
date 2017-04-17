#pragma once
#include "Console.h"
#include <memory>
#include <string>
#include <vector>
class Console;
class ArgsParser;
struct ProgramArgs;

class Program
{
   friend class ProgramTests;
private:
   std::unique_ptr<const Console> _console;
   std::unique_ptr<const ArgsParser> _argsParser;
   static const std::string CommandLineUsage;
public:
   Program();
   ~Program();
   int Main(int argc, char* argv[]) const;
   virtual int VectorMain(const std::vector<std::string>& args) const;
   virtual int ArgsMain(const ProgramArgs& programArgs) const;
};
