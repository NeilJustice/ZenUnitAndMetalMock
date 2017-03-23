#pragma once
#include <experimental/filesystem>

namespace ZenUnit
{
   template<typename T>
   struct is_quoted_when_printed : std::integral_constant<bool,
      std::is_same<std::string, typename std::decay<T>::type>::value ||
      std::is_same<char const*, typename std::decay<T>::type>::value ||
      std::is_same<char*, typename std::decay<T>::type>::value ||
      std::is_same<std::experimental::filesystem::path, typename std::decay<T>::type>::value>
   {
   };
}
