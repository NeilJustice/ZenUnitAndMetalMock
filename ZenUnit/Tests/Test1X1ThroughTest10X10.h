#pragma once
#include "ZenUnit/Tests/TestNXN.h"
#include "ZenUnit/Utils/Tuple.h"

namespace ZenUnit
{
   template<
      typename TestClassType,
      typename Arg1Type,
      typename... TestCaseArgTypes>
   class Test1X1 : public TestNXN<TestClassType, 1, TestCaseArgTypes...>
   {
   public:
      using Test1X1MemberFunction = void (TestClassType::*)(Arg1Type);
   private:
      const Test1X1MemberFunction _test1X1MemberFunction;
   public:
      Test1X1(
         const char* testClassName, const char* testName, Test1X1MemberFunction test1X1MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 1, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test1X1MemberFunction(test1X1MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call1ArgMemberFunction(
            testClass, _test1X1MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename... TestCaseArgTypes>
   class Test2X2 : public TestNXN<TestClassType, 2, TestCaseArgTypes...>
   {
   public:
      using Test2X2MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type);
   private:
      const Test2X2MemberFunction _test2X2MemberFunction;
   public:
      Test2X2(
         const char* testClassName, const char* testName, Test2X2MemberFunction test2X2MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 2, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test2X2MemberFunction(test2X2MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call2ArgMemberFunction(
            testClass, _test2X2MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename... TestCaseArgTypes>
   class Test3X3 : public TestNXN<TestClassType, 3, TestCaseArgTypes...>
   {
   public:
      using Test3X3MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type);
   private:
      const Test3X3MemberFunction _test3X3MemberFunction;
   public:
      Test3X3(
         const char* testClassName, const char* testName, Test3X3MemberFunction test3X3MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 3, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test3X3MemberFunction(test3X3MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call3ArgMemberFunction(
            testClass, _test3X3MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename... TestCaseArgTypes>
   class Test4X4 : public TestNXN<TestClassType, 4, TestCaseArgTypes...>
   {
   public:
      using Test4X4MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type);
   private:
      const Test4X4MemberFunction _test4X4MemberFunction;
   public:
      Test4X4(
         const char* testClassName, const char* testName, Test4X4MemberFunction test4X4MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 4, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test4X4MemberFunction(test4X4MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call4ArgMemberFunction(
            testClass, _test4X4MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename... TestCaseArgTypes>
   class Test5X5 : public TestNXN<TestClassType, 5, TestCaseArgTypes...>
   {
   public:
      using Test5X5MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type);
   private:
      const Test5X5MemberFunction _test5X5MemberFunction;
   public:
      Test5X5(
         const char* testClassName, const char* testName, Test5X5MemberFunction test5X5MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 5, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test5X5MemberFunction(test5X5MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call5ArgMemberFunction(
            testClass, _test5X5MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename... TestCaseArgTypes>
   class Test6X6 : public TestNXN<TestClassType, 6, TestCaseArgTypes...>
   {
   public:
      using Test6X6MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type);
   private:
      const Test6X6MemberFunction _test6X6MemberFunction;
   public:
      Test6X6(
         const char* testClassName, const char* testName, Test6X6MemberFunction test6X6MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 6, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test6X6MemberFunction(test6X6MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call6ArgMemberFunction(
            testClass, _test6X6MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename... TestCaseArgTypes>
   class Test7X7 : public TestNXN<TestClassType, 7, TestCaseArgTypes...>
   {
   public:
      using Test7X7MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type);
   private:
      const Test7X7MemberFunction _test7X7MemberFunction;
   public:
      Test7X7(
         const char* testClassName, const char* testName, Test7X7MemberFunction test7X7MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 7, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test7X7MemberFunction(test7X7MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call7ArgMemberFunction(
            testClass, _test7X7MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type,
      typename... TestCaseArgTypes>
   class Test8X8 : public TestNXN<TestClassType, 8, TestCaseArgTypes...>
   {
   public:
      using Test8X8MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type);
   private:
      const Test8X8MemberFunction _test8X8MemberFunction;
   public:
      Test8X8(
         const char* testClassName, const char* testName, Test8X8MemberFunction test8X8MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 8, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test8X8MemberFunction(test8X8MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call8ArgMemberFunction(
            testClass, _test8X8MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type,
      typename Arg9Type,
      typename... TestCaseArgTypes>
   class Test9X9 : public TestNXN<TestClassType, 9, TestCaseArgTypes...>
   {
   public:
      using Test9X9MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type);
   private:
      const Test9X9MemberFunction _test9X9MemberFunction;
   public:
      Test9X9(
         const char* testClassName, const char* testName, Test9X9MemberFunction test9X9MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 9, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test9X9MemberFunction(test9X9MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call9ArgMemberFunction(
            testClass, _test9X9MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };

   template<
      typename TestClassType,
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type,
      typename... TestCaseArgTypes>
   class Test10X10 : public TestNXN<TestClassType, 10, TestCaseArgTypes...>
   {
   public:
      using Test10X10MemberFunction = void (TestClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type);
   private:
      const Test10X10MemberFunction _test10X10MemberFunction;
   public:
      Test10X10(
         const char* testClassName, const char* testName, Test10X10MemberFunction test10X10MemberFunction,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 10, TestCaseArgTypes...>(
            testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test10X10MemberFunction(test10X10MemberFunction)
      {
      }

      void NXNTestBody(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call10ArgMemberFunction(
            testClass, _test10X10MemberFunction, testCaseArgsIndex, this->_testCaseArgs);
      }
   };
}
