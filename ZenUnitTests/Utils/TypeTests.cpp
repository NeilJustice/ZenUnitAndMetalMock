#include "pch.h"
#include "ZenUnit/Utils/Type.h"
#include <atomic>

class TypeTestsBase {};
class TypeTestsDerived : public TypeTestsBase {};

namespace ZenUnit
{
   TESTS(TypeTests)
   FACT(GetName_NonClassNonStructType_ReturnsTypeName)
   FACT(GetName_ClassType_ReturnsTypeNameMinusClassSpace)
   FACT(GetName_StructType_ReturnsTypeNameMinusStructSpace)
   FACT(GetName_DeclaredAndRuntimeTypeIsDerived_ReturnsDerived)
   FACT(GetName_ThrownExceptionSubclass_ReturnsSubclassNameAndNotException)
   FACT(GetNameT_NonClassNonStructType_ReturnsTypeName)
   FACT(GetNameT_ClassType_ReturnsTypeNameMinusClassSpace)
   FACT(GetNameT_StructType_ReturnsTypeNameMinusStructSpace)
   FACT(GetNameT_ThrownExceptionSubclass_ReturnsBaseClassNameAndNotSubclassName)
   BEGINPROOF

   class C {};
   struct S {};
   template<typename T>
   class TemplateClass {};

   TEST(GetName_NonClassNonStructType_ReturnsTypeName)
   {
      ARE_EQUAL("int", *Type::GetName(1));
#ifdef __linux__
      ARE_EQUAL("decltype(nullptr)", *Type::GetName(nullptr));
      ARE_EQUAL("char [1]", *Type::GetName(""));
      ARE_EQUAL("char [2]", *Type::GetName("a"));
      const char* const ccp = "hello";
      ARE_EQUAL("char const*", *Type::GetName(ccp));
#elif _WIN32
      ARE_EQUAL("std::nullptr_t", *Type::GetName(nullptr));
      ARE_EQUAL("char const [1]", *Type::GetName(""));
      ARE_EQUAL("char const [2]", *Type::GetName("a"));
      const char* const ccp = "hello";
   #if _WIN64
      ARE_EQUAL("char const * __ptr64", *Type::GetName(ccp));
   #elif _WIN32
      ARE_EQUAL("char const *", *Type::GetName(ccp));
   #endif
#endif
   }

   TEST(GetName_ClassType_ReturnsTypeNameMinusClassSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::C", *Type::GetName(C()));
#ifdef __linux__
      ARE_EQUAL("std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >", *Type::GetName<string>());
      ARE_EQUAL("std::ostream", *Type::GetName<decltype(cout)>());
#elif _WIN32
      ARE_EQUAL("std::basic_string<char,std::char_traits<char>,std::allocator<char> >", *Type::GetName(string()));
      ARE_EQUAL("std::basic_ostream<char,std::char_traits<char> >", *Type::GetName(cout));
   #endif
   }

   TEST(GetName_StructType_ReturnsTypeNameMinusStructSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::S", *Type::GetName(S()));
      ARE_EQUAL("std::atomic<int>", *Type::GetName(atomic<int>()));
   }

   TEST(GetName_DeclaredAndRuntimeTypeIsDerived_ReturnsDerived)
   {
      const TypeTestsDerived derived{};
      ARE_EQUAL("TypeTestsDerived", *Type::GetName(derived));
   }

   TEST(GetName_ThrownExceptionSubclass_ReturnsSubclassNameAndNotException)
   {
      try
      {
         throw logic_error("message");
      }
      catch (const exception& e)
      {
         ARE_EQUAL("std::logic_error", *Type::GetName(e));
      }
   }

   TEST(GetNameT_NonClassNonStructType_ReturnsTypeName)
   {
      ARE_EQUAL("int", *Type::GetName<int>());
#ifdef __linux__
      ARE_EQUAL("decltype(nullptr)", *Type::GetName<std::nullptr_t>());
      ARE_EQUAL("char [1]", *Type::GetName<decltype("")>());
      ARE_EQUAL("char [2]", *Type::GetName<decltype("a")>());
      ARE_EQUAL("char const*", *Type::GetName<const char*>());
#elif _WIN32
      ARE_EQUAL("std::nullptr_t", *Type::GetName<std::nullptr_t>());
      ARE_EQUAL("char const [1]", *Type::GetName<decltype("")>());
      ARE_EQUAL("char const [2]", *Type::GetName<decltype("a")>());
   #if _WIN64
      ARE_EQUAL("char const * __ptr64", *Type::GetName<const char*>());
   #elif _WIN32
      ARE_EQUAL("char const *", *Type::GetName<const char*>());
   #endif
#endif
   }

   TEST(GetNameT_ClassType_ReturnsTypeNameMinusClassSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::TemplateClass<ZenUnit::TypeTests::C>", *Type::GetName<TemplateClass<C>>());
      ARE_EQUAL("ZenUnit::TypeTests::TemplateClass<ZenUnit::TypeTests::S>", *Type::GetName<TemplateClass<S>>());
      ARE_EQUAL("ZenUnit::TypeTests::C", *Type::GetName<C>());
   #ifdef __linux__
      ARE_EQUAL("std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >", *Type::GetName<string>());
      ARE_EQUAL("std::ostream", *Type::GetName<decltype(cout)>());
   #elif _WIN32
      ARE_EQUAL("std::basic_string<char,std::char_traits<char>,std::allocator<char> >", *Type::GetName<string>());
      ARE_EQUAL("std::basic_ostream<char,std::char_traits<char> >", *Type::GetName<decltype(cout)>());
   #endif
   }

   TEST(GetNameT_StructType_ReturnsTypeNameMinusStructSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::S", *Type::GetName<S>());
      ARE_EQUAL("std::atomic<int>", *Type::GetName<atomic<int>>());
   }

   TEST(GetNameT_ThrownExceptionSubclass_ReturnsBaseClassNameAndNotSubclassName)
   {
      try
      {
         throw logic_error("message");
      }
   #ifdef _WIN32
   #pragma warning(push)
   // Disable unreference local variable because MSVC does not count decltype(localVariable) as referencing localVariable
   #pragma warning(disable: 4101)
   #endif
      catch (const exception& e)
   #ifdef _WIN32
   #pragma warning(pop)
   #endif
      {
         ARE_EQUAL("std::exception", *Type::GetName<decltype(e)>());
      }
   }

   }; RUN(TypeTests)
}
