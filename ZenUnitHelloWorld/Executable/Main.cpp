#include "StaticLibrary/Program.h"

int main(int argc, char* argv[])
{
   Program program;
   int exitCode = program.Main(argc, argv);
   return exitCode;
}
