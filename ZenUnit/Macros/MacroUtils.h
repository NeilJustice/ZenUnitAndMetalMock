#pragma once

#define DOTOKENJOIN(a, b) a##b
#define TOKENJOIN(a, b) DOTOKENJOIN(a, b)

#define DOVATEXT(placeholder, ...) #__VA_ARGS__
#define VATEXT(...) DOVATEXT("", __VA_ARGS__)
#define VA_TEXT_ARGS(...) VATEXT(__VA_ARGS__), ##__VA_ARGS__

#define Comma ,

// Noinlining error-handling code adjacent to hot path code
// can increase the performance of hot path code
// by minimizing the error-handling code's load on instruction caches
#ifdef __linux__
   #define NOINLINE __attribute__((noinline))
#elif _WIN32
   #define NOINLINE __declspec(noinline)
#endif
