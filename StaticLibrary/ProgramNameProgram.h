#pragma once
class Console;
struct ProgramArgs;

class ProgramNameProgram
{
   friend class ProgramNameProgramTests;
private:
   std::unique_ptr<const Console> _console;
public:
   ProgramNameProgram();
   virtual ~ProgramNameProgram();
   int Main(int argc, char* argv[]) const;
   virtual int VectorMain(const std::vector<std::string>& args) const;
};
