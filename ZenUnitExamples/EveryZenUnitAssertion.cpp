#include "pch.h"

struct Struct
{
   int firstField = 0;
   char secondField = 0;
};

namespace ZenUnit
{
   template<>
   struct Equalizer<Struct>
   {
      static void AssertEqual(const Struct& expectedStruct, const Struct& actualStruct)
      {
         ARE_EQUAL(expectedStruct.firstField, actualStruct.firstField);
         ARE_EQUAL(expectedStruct.secondField, actualStruct.secondField);
      }
   };
}

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

   // Pointers
   IS_NULL(nullptr);
   IS_NOT_NULL(std::make_unique<int>());
   const int* operatorNewedInt = new int;
   POINTER_WAS_NEWED(operatorNewedInt);
   const int* operatorNewedIntArray = new int[3];
   ARRAY_WAS_NEWED(operatorNewedIntArray);
   POINTEES_EQUAL(&x, &x);

   // Data Structures
   VECTORS_EQUAL(std::vector<int>{0}, std::vector<int>{0});
   MAPS_EQUAL((std::map<int, int>{}), (std::map<int, int>{}));
   MAPS_EQUAL((std::unordered_map<int, int>{}), (std::unordered_map<int, int>{}));
   SETS_EQUAL(std::set<int>{}, std::set<int>{});
   SETS_EQUAL(std::unordered_set<int>{}, std::unordered_set<int>{});
   CONTAINS_ELEMENT(0, std::vector<int>{0});
   IS_EMPTY(std::vector<int>());
   STD_ARRAYS_EQUAL((std::array<int, 5>{}), (std::array<int, 5>{}));

   // Exceptions
   THROWS([]{ throw std::runtime_error("what"); }(), std::runtime_error, "what");
   DOES_NOT_THROW([]{}());

   // Equalizers
   SETUP_EQUALIZER_THROWS_TEST(Struct);
   EQUALIZER_THROWS_FOR_FIELD(Struct, firstField, 1);
   EQUALIZER_THROWS_FOR_FIELD(Struct, secondField, 'A');
}

RUN_TESTS(EveryZenUnitAssertion)
