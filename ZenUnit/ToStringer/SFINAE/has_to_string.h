#pragma once

namespace ZenUnit
{
   template<typename T>
   class has_to_string
   {
   private:
      template<typename U>
      static auto SFINAE(const U& value) -> decltype(std::to_string(value));
      static std::false_type SFINAE(...);
   public:
      static const bool value = std::is_same<std::string,
         decltype(SFINAE(std::declval<T>()))>::value;
   };

#ifdef __linux__
   template<typename T>
   const bool has_to_string<T>::value;
#endif
}
