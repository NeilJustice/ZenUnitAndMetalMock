#include "pch.h"

namespace Namespace
{
   int f(int, int) { return 0; }
}

ZENMOCK_NONVOID2_STATIC(int, Namespace, f, int, int)