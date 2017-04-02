#pragma once
#include "ZenUnit/ZenMock/ZEN.h"
#include "ZenUnit/Utils/Type.h"

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
   };
}
