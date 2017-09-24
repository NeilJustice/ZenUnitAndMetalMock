#pragma once
#include <regex>
#include <unordered_map>
#ifdef __linux__
#include "ZenUnit/Utils/AssertTrue.h"
#include <cxxabi.h>
#endif

namespace ZenUnit
{
   class Type
   {
      friend class TypeTests;
   private:
      // Demangling is expensive so this demangled type name cache exists
      static std::unordered_map<const char*, std::string>& MangledToDemangledTypeNameMap();
   public:
      template<typename T>
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4100) // 'variable' unreferenced formal parameter (MSVC does not count typeid(variable) as referencing variable
#endif
      static const std::string* GetName(const T& variable)
#ifdef _WIN32
#pragma warning(pop)
#endif
      {
         return TypeInfoToTypeName(typeid(variable));
      }

      template<typename T>
      static const std::string* GetName()
      {
         return TypeInfoToTypeName(typeid(T));
      }
   private:
      static const std::string* TypeInfoToTypeName(const std::type_info& typeInfo)
      {
         const char* const mangledTypeName = typeInfo.name();
         std::unordered_map<const char*, std::string>&
            mangledToDemangledTypeName = MangledToDemangledTypeNameMap();
         if (const std::unordered_map<const char*, std::string>::const_iterator
             findIter = mangledToDemangledTypeName.find(mangledTypeName);
             findIter == mangledToDemangledTypeName.end())
         {
            const std::string demangledTypeName = Demangle(mangledTypeName);
            const std::pair<std::unordered_map<const char*, std::string>::const_iterator, bool>
               emplaceResult = mangledToDemangledTypeName.emplace(mangledTypeName, demangledTypeName);
            const std::string* const cachedDemangledTypeName = &emplaceResult.first->second;
            return cachedDemangledTypeName;
         }
         else
         {
            const std::string* cachedDemangledTypeName = &findIter->second;
            return cachedDemangledTypeName;
         }
      }

#ifdef __linux__
      static std::string Demangle(const char* mangledTypeName)
      {
         int demangleStatus = -1;
         std::unique_ptr<char, void(*)(void*)> demangledTypeNamePointer(
            abi::__cxa_demangle(mangledTypeName, nullptr, nullptr, &demangleStatus),
            std::free);
         assert_true(demangleStatus == 0);
         std::string demangledTypeName(demangledTypeNamePointer.get());
         return demangledTypeName;
      }
#elif _WIN32
      static std::string Demangle(const char* mangledTypeName)
      {
         static const std::regex classStructPattern("(class |struct )");
         const std::string typeNameMinusClassAndStruct
            = std::regex_replace(mangledTypeName, classStructPattern, "");
         return typeNameMinusClassAndStruct;
      }
#endif
   };
}
