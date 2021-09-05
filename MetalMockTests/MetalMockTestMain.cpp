#include "pch.h"

class A
{
public:
   virtual void ZeroArgFunctionA() {}
   virtual void ZeroArgFunctionB() {}

   virtual void OneArgFunctionA(int) {}
   virtual void OneArgFunctionB(int) {}

   virtual void TwoArgsFunctionA(int, int) {}
   virtual void TwoArgsFunctionB(int, int) {}

   virtual ~A() = default;
};

class AMock : public Metal::Mock<A>
{
public:
   METALMOCK_VOID0(ZeroArgFunctionA)
   METALMOCK_VOID0(ZeroArgFunctionB)

   METALMOCK_VOID1(OneArgFunctionA, int)
   METALMOCK_VOID1(OneArgFunctionB, int)

   METALMOCK_VOID2(TwoArgsFunctionA, int, int)
   METALMOCK_VOID2(TwoArgsFunctionB, int, int)
};

TESTS(ZZTests)
AFACT(Test)
EVIDENCE

TEST(Test)
{
   AMock amock;
   amock.ZeroArgFunctionAMock.Expect();
   amock.ZeroArgFunctionA();
   amock.ZeroArgFunctionAMock.CalledOnce();
}

RUN_TESTS(ZZTests)

int main(int argc, char* argv[])
{
   ZenUnit::globalZenUnitMode.selfTest = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
