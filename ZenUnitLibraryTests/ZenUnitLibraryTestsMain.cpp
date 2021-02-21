#include "pch.h"

//int main()
//{
//   const int lowercaseA = static_cast<int>('a');
//   const int uppercaseA = static_cast<int>('A');
//   const int lowercaseZ = static_cast<int>('z');
//   const int uppercaseZ = static_cast<int>('Z');
//   for (size_t i = 65; i <= 90; ++i)
//   {
//      const char c = static_cast<char>(i);
//      cout << c << '\n';
//   }
//   cout << '\n';
//   for (size_t i = 97; i <= 122; ++i)
//   {
//      const char c = static_cast<char>(i);
//      cout << c << '\n';
//   }
//}

int main(int argc, char* argv[])
{
   ZenUnit::globalZenUnitMode.selfTest = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
