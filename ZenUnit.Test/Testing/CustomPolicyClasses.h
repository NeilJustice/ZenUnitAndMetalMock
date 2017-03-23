#pragma once

template<typename T>
struct CustomLessComparator : public less<T> {};

template<typename T>
struct CustomAllocator : public allocator<T> {};

template<typename T>
struct CustomHasher : public hash<T> {};

template<typename T>
struct CustomEqualityComparator : public equal_to<T> {};
