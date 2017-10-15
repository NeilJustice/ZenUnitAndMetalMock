#include "pch.h"
#include "ZenUnit/Utils/Iteration/ExtraArgForEacher.h"

namespace ZenUnit
{
   TESTS(ForEacherExtraArgTests)
   AFACT(NonConstExtraArgForEach_EmptyCollection_DoesNothing)
   AFACT(NonConstExtraArgForEach_OneItemCollection_CallsFuncOnItemOnce)
   AFACT(NonConstExtraArgForEach_TwoItemCollection_CallsFuncOnItemTwice)
   EVIDENCE

   ExtraArgForEacher<vector<int>, function<void(int, int)>, int> _forEacherExtraArg;

   vector<pair<int, int>> calls;
   void Function(int element, int extraArg)
   {
      calls.emplace_back(element, extraArg);
   }

   auto BindFunction()
   {
      return bind(&ForEacherExtraArgTests::Function, this, placeholders::_1, placeholders::_2);
   }

   TEST(NonConstExtraArgForEach_EmptyCollection_DoesNothing)
   {
      vector<int> emptyVector;
      //
      _forEacherExtraArg.NonConstExtraArgForEach(&emptyVector, BindFunction(), 0);
      //
      ARE_EQUAL(0, calls.size());
   }

   TEST(NonConstExtraArgForEach_OneItemCollection_CallsFuncOnItemOnce)
   {
      vector<int> oneItemVector { 1 };
      //
      _forEacherExtraArg.NonConstExtraArgForEach(&oneItemVector, BindFunction(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   TEST(NonConstExtraArgForEach_TwoItemCollection_CallsFuncOnItemTwice)
   {
      vector<int> oneItemVector { 1, 2 };
      //
      _forEacherExtraArg.NonConstExtraArgForEach(&oneItemVector, BindFunction(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 },
         { 2, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   }; RUNTESTS(ForEacherExtraArgTests)
}
