#include "pch.h"

struct Struct
{
   int firstField = 0;
   char secondField = 0;
};

template<>
struct ZenUnitEqualizer<Struct>
{
   static void AssertEqual(const Struct& expectedStruct, const Struct& actualStruct)
   {
      ARE_EQUAL(expectedStruct.firstField, actualStruct.firstField);
      ARE_EQUAL(expectedStruct.secondField, actualStruct.secondField);
   }
};

TESTS(CallAllMacrosTests)
FACT(CallAllMacros)
EVIDENCE

TEST(CallAllMacros)
{
   // Values
   std::string s1 = "Hello";
   std::string s2 = s1;
   ARE_COPIES(s1, s2);
   ARE_EQUAL(0, 0);
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
   const int* dynamicallyAllocatedInt = new int;
   POINTER_WAS_NEWED(dynamicallyAllocatedInt);
   const int* dynamicallyAllocatedArray = new int[3];
   ARRAY_WAS_NEWED(dynamicallyAllocatedArray);
   POINTEES_EQUAL(&x, &x);

   // Data Structures
   IS_EMPTY(std::vector<int>());
   CONTAINS(0, std::vector<int>{0});
   VECTORS_EQUAL(std::vector<int>{0}, std::vector<int>{0});
   MAPS_EQUAL((std::map<int, int>{}), (std::map<int, int>{}));
   MAPS_EQUAL((std::unordered_map<int, int>{}), (std::unordered_map<int, int>{}));
   SETS_EQUAL(std::set<int>{}, std::set<int>{});
   SETS_EQUAL(std::unordered_set<int>{}, std::unordered_set<int>{});

   // Exceptions
   THROWS([]{ throw std::runtime_error("what"); }(), std::runtime_error, "what");
   NOTHROWS([]{}());

   // Regular Expressions
   REGEX_MATCHES(R"(\d\d\d)", "123");

   // ZenUnitEqualizer
   EQUALIZER_THROWS_INIT(Struct);
   EQUALIZER_THROWS(Struct, firstField, 1);
   EQUALIZER_THROWS(Struct, secondField, 'A');
}

RUNTESTS(CallAllMacrosTests)
