#include "pch.h"
#include "Program.h"

int Program::Main(int argc, char* argv[]) const
{
   vector<string> args = ArgcArgvToStringVector(argc, argv);
   return ArgsMain(args);
}

int Program::ArgsMain(const vector<string>&) const
{
   cout << "Hello ZenUnit-tested program\n";
   return 0;
}

vector<string> Program::ArgcArgvToStringVector(int argc, char* argv[])
{
	vector<string> args;
   args.reserve(argc);
   for_each(argv, argv + argc, [&](char* arg) { args.emplace_back(arg); });
	return args;
}
