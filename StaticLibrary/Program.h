#pragma once
#include <memory>
#include <vector>
class Console;
struct ProgramArgs;

class Program
{
   friend class ProgramTests;
private:
   std::unique_ptr<const Console> _console;
public:
   Program();
   virtual ~Program();
   int Main(int argc, char* argv[]) const;
   virtual int VectorMain(const std::vector<std::string>& args) const;
};
