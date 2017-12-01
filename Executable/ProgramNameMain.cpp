#include <memory>
#include <vector>
#include "StaticLibrary/ProgramNameProgram.h"

int main(int argc, char* argv[])
{
   ProgramNameProgram program;
   const int exitCode = program.Main(argc, argv);
   return exitCode;
}
