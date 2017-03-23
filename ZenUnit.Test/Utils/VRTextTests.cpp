#include "pch.h"
#include "ZenUnit/Utils/VRText.h"

namespace ZenUnit
{
   TESTS(VRTextTests)
   SPEC(Constructor_Int_SetsFields)
   SPEC(Constructor_Double_SetsFields)
   SPEC(Constructor_Float_SetsFields)
   SPEC(Constructor_ConstCharPointer_SetsFields)
   SPEC(Constructor_String_SetsFields)
   SPEC(Constructor_NonConstCharacterArray_SetsFields)
   SPECEND

   TEST(Constructor_Int_SetsFields)
   {
      int x = 1;
      VRText<int> vrtextInt(x, "1");
      ARE_EQUAL(1, vrtextInt.value);
      ARE_EQUAL("1", vrtextInt.text);
   }

   TEST(Constructor_Double_SetsFields)
   {
      double d = 1.1;
      VRText<double> vrtextDouble(d, "1.1");
      ARE_EQUAL(1.1, vrtextDouble.value);
      ARE_EQUAL("1.1", vrtextDouble.text);
   }

   TEST(Constructor_Float_SetsFields)
   {
      float f = 1.1f;
      VRText<float> vrtextFloat(f, "1.1f");
      ARE_EQUAL(1.1f, vrtextFloat.value);
      ARE_EQUAL("1.1f", vrtextFloat.text);
   }

   TEST(Constructor_ConstCharPointer_SetsFields)
   {
      const char* ccp = "ccp";
      VRText<const char*> vrtextCCP(ccp, "text");
      ARE_EQUAL("ccp", vrtextCCP.value);
      ARE_EQUAL("text", vrtextCCP.text);
   }

   TEST(Constructor_String_SetsFields)
   {
      string str = "str";
      VRText<string> vrtextCCP(str, "text");
      ARE_EQUAL("str", vrtextCCP.value);
      ARE_EQUAL("text", vrtextCCP.text);
   }

   TEST(Constructor_NonConstCharacterArray_SetsFields)
   {
      char chars2[] = { 'A', 0 };
      VRText<decltype(chars2)> vrtext2(chars2, "text2");
      // Test for assignability to a non-const char*
      char* chars2Variable = vrtext2.value;
      ARE_EQUAL("A", chars2Variable);
      ARE_EQUAL("text2", vrtext2.text);

      char chars3[] = { 'A', 'B', 0 };
      VRText<decltype(chars3)> vrtext3(chars3, "text3");
      // Test for assignability to a non-const char*
      char* chars3Variable = vrtext3.value;
      ARE_EQUAL("AB", chars3Variable);
      ARE_EQUAL("text3", vrtext3.text);
   }

   }; RUN(VRTextTests)
}
