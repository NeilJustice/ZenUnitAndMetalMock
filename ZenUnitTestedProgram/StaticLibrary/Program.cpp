#include "Program.h"
#include <algorithm>
#include <iostream>

int Program::Main(int argc, char* argv[]) const
{
   std::vector<std::string> args = ArgcArgvToStringVector(argc, argv);
   return ArgsMain(args);
}

int Program::ArgsMain(const std::vector<std::string>&) const
{
   std::cout << "Hello ZenUnit-tested program\n";
   return 0;
}

std::vector<std::string> Program::ArgcArgvToStringVector(int argc, char* argv[])
{
	std::vector<std::string> args;
   args.reserve(argc);
   std::for_each(argv, argv + argc, [&](char* arg) { args.emplace_back(arg); });
	return args;
}
