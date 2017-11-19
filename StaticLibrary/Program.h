#pragma once
class Console;
struct ProgramArgs;

class Program
{
   friend class ProgramTests;
private:
   unique_ptr<const Console> _console;
   static const string CommandLineUsage;
public:
   Program();
   virtual ~Program();
   int Main(int argc, char* argv[]) const;
   virtual int VectorMain(const vector<string>& args) const;
};
