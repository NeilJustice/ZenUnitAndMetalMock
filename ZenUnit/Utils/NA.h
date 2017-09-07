#pragma once

template<typename T>
struct NA
{
   operator T() const { return T{}; }
};
