#include "pch.h"
#include <atomic>
#include "ZenUnit/Utils/Type.h"

class TypeTestsBase {};
class TypeTestsDerived : public TypeTestsBase {};

namespace ZenUnit
{
   TESTS(TypeTests)
   SPEC(GetName_NonClassNonStructType_ReturnsTypeName)
   SPEC(GetName_ClassType_ReturnsTypeNameMinusClassSpace)
   SPEC(GetName_StructType_ReturnsTypeNameMinusStructSpace)
   SPEC(GetName_DeclaredAndRuntimeTypeIsDerived_ReturnsDerived)
   SPEC(GetName_ThrownExceptionSubclass_ReturnsSubclassNameAndNotException)
   SPEC(GetNameT_NonClassNonStructType_ReturnsTypeName)
   SPEC(GetNameT_ClassType_ReturnsTypeNameMinusClassSpace)
   SPEC(GetNameT_StructType_ReturnsTypeNameMinusStructSpace)
   SPEC(GetNameT_ThrownExceptionSubclass_ReturnsBaseClassNameAndNotSubclassName)
   SPECEND

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
      ARE_EQUAL("char const * __ptr64", *Type::GetName(ccp));
   #endif
   }

   TEST(GetName_ClassType_ReturnsTypeNameMinusClassSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::C", *Type::GetName(C()));
   #ifdef __linux__
      ARE_EQUAL("std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >", *Type::GetName<string>());
      ARE_EQUAL("std::ostream", *Type::GetName<decltype(cout)>());
      ARE_EQUAL("int (_IO_FILE*)", *Type::GetName<decltype(ferror)>());
   #elif _WIN32
      ARE_EQUAL("std::basic_string<char,std::char_traits<char>,std::allocator<char> >", *Type::GetName(string()));
      ARE_EQUAL("std::basic_ostream<char,std::char_traits<char> >", *Type::GetName(cout));
      ARE_EQUAL("int __cdecl(_iobuf * __ptr64)", *Type::GetName(ferror));
   #endif
   }

   TEST(GetName_StructType_ReturnsTypeNameMinusStructSpace)
   {
      ARE_EQUAL("ZenUnit::TypeTests::S", *Type::GetName(S()));
      ARE_EQUAL("std::atomic<int>", *Type::GetName(atomic<int>()));
   }

   TEST(GetName_DeclaredAndRuntimeTypeIsDerived_ReturnsDerived)
   {
      const TypeTestsDerived derived;
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
      ARE_EQUAL("char const * __ptr64", *Type::GetName<const char*>());
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
      ARE_EQUAL("int (_IO_FILE*)", *Type::GetName<decltype(ferror)>());
   #elif _WIN32
      ARE_EQUAL("std::basic_string<char,std::char_traits<char>,std::allocator<char> >", *Type::GetName<string>());
      ARE_EQUAL("std::basic_ostream<char,std::char_traits<char> >", *Type::GetName<decltype(cout)>());
      ARE_EQUAL("int __cdecl(_iobuf * __ptr64)", *Type::GetName<decltype(ferror)>());
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
