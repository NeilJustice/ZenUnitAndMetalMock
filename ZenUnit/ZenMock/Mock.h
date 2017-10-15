#pragma once
#include "ZenUnit/Utils/Type.h"
#include "ZenUnit/ZenMock/ZEN.h"

namespace Zen
{
   template<typename ZenMockedClass>
   class Mock : public ZenMockedClass
   {
   public:
      template<typename... ArgTypes>
      explicit Mock(ArgTypes&&... args)
         : ZenMockedClass(std::forward<ArgTypes>(args)...)
      {
      }

      static const std::string* ZenMockedClassName()
      {
         const std::string* const zenMockedClassName = ZenUnit::Type::GetName<ZenMockedClass>();
         return zenMockedClassName;
      }

      static_assert(std::has_virtual_destructor<ZenMockedClass>::value,
         "ZenMocked classes must define a virtual destructor so as to not introduce a memory leak as detected by Clang AddressSanitizer.");
   };
}
