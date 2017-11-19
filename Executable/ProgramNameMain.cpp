#include <iostream>
#include <memory>
#include <vector>
using namespace std;
#include "StaticLibrary/Program.h"

int main(int argc, char* argv[])
{
   Program program;
   const int exitCode = program.Main(argc, argv);
   return exitCode;
}
