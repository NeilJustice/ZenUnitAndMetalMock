#pragma once

namespace ZenUnit
{
   template<typename T>
   class has_ostream_left_shift
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(os << value);
      static std::false_type SFINAE(...);
   public:
      static const bool value = std::is_same<std::ostream&,
         decltype(SFINAE(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

#ifdef __linux__
   template<typename T>
   const bool has_ostream_left_shift<T>::value;
#endif
}
