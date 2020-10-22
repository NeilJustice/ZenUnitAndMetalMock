#include "pch.h"

struct Struct
{
   int firstField = 0;
   char secondField = 0;
};

namespace ZenUnit
{
   template<>
   class Equalizer<Struct>
   {
   public:
      static void AssertEqual(const Struct& expectedStruct, const Struct& actualStruct)
      {
         ARE_EQUAL(expectedStruct.firstField, actualStruct.firstField);
         ARE_EQUAL(expectedStruct.secondField, actualStruct.secondField);
      }
   };
}

//void OverloadedFunction(int) {}
//void OverloadedFunction(std::string_view) {}

TESTS(EveryZenUnitAssertion)
AFACT(CallAllMacros)
EVIDENCE

TEST(CallAllMacros)
{
   // Values
   ARE_EQUAL(0, 0);
   std::string s1 = "Hello";
   std::string s2 = s1;
   ARE_COPIES(s1, s2);
   int x = 0, y = 0;
   ARE_SAME(x, x);
   ARE_NOT_SAME(x, y);
   IS_TRUE(true);
   IS_FALSE(false);
   IS_ZERO(0);

   // Functions
   STD_FUNCTION_TARGETS(::exit, std::function<void(int)>(::exit));

   // Travis CI GCC error when compiling these STD_FUNCTION_TARGETS_OVERLOAD statemetns:
   // types ‘const ExpectedStdFunctionTargetType’ and ‘void(std::string_view)’ {aka ‘void(std::basic_string_view<char>)’} have incompatible cv-qualifiers

   //using ExpectedIntOverloadType = void(*)(int);
   //std::function<void(int)> overloadedIntStdFunction = static_cast<ExpectedIntOverloadType>(::OverloadedFunction);
   //STD_FUNCTION_TARGETS_OVERLOAD(ExpectedIntOverloadType, ::OverloadedFunction, overloadedIntStdFunction);

   //using ExpectedStringViewOverloadType = void(*)(std::string_view);
   //std::function<void(std::string_view)> overloadedStringViewStdFunction = static_cast<ExpectedStringViewOverloadType>(::OverloadedFunction);
   //STD_FUNCTION_TARGETS_OVERLOAD(ExpectedStringViewOverloadType, ::OverloadedFunction, overloadedStringViewStdFunction);

   // Pointers
   IS_NULLPTR(nullptr);
   IS_NOT_NULLPTR(std::make_unique<int>());
   const int* operatorNewedInt = new int;
   DELETE_TO_ASSERT_NEWED(operatorNewedInt);
   const int* operatorNewedIntArray = new int[3];
   ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(operatorNewedIntArray);
   POINTEES_ARE_EQUAL(&x, &x);

   // Data Structures
   VECTORS_ARE_EQUAL(std::vector<int>{0}, std::vector<int>{0});
   MAPS_ARE_EQUAL((std::map<int, int>{}), (std::map<int, int>{}));
   MAPS_ARE_EQUAL((std::unordered_map<int, int>{}), (std::unordered_map<int, int>{}));
   SETS_ARE_EQUAL(std::set<int>{}, std::set<int>{});
   SETS_ARE_EQUAL(std::unordered_set<int>{}, std::unordered_set<int>{});
   CONTAINS_ELEMENT(0, std::vector<int>{0});
   IS_EMPTY(std::vector<int>());
   STD_ARRAYS_EQUAL((std::array<int, 5>{}), (std::array<int, 5>{}));

   // Exceptions
   THROWS_EXCEPTION([]{ throw std::runtime_error("what"); }(), std::runtime_error, "what");
   DOES_NOT_THROW([]{}());

   // Equalizers
   SETUP_EQUALIZER_TEST(Struct);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Struct, firstField, 1);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Struct, secondField, 'A');
}

RUN_TESTS(EveryZenUnitAssertion)
