#include "pch.h"

class Mutex
{
public:
   virtual void Lock() {}
   virtual void Unlock() {}
   virtual ~Mutex() = default;
};

class MutexMock : public Zen::Mock<Mutex>
{
public:
   ZENMOCK_VOID0(Lock)
   ZENMOCK_VOID0(Unlock)
};

class Action
{
public:
   virtual void Act() {}
   virtual ~Action() = default;
};

class ActionMock : public Zen::Mock<Action>
{
public:
   ZENMOCK_VOID0(Act)
};

TESTS(Tests)
AFACT(Test)
EVIDENCE

TEST(Test)
{
   MutexMock mutexMock;
   ActionMock actionMock;
   mutexMock.LockMock.Expect();
   actionMock.ActMock.Expect();
   mutexMock.UnlockMock.Expect();
   //
   mutexMock.Lock();
   actionMock.Act();
   mutexMock.Unlock();
   //
   //mutexMock.LockMock.CalledOnce().Then(
   //actionMock.ActMock.CalledOnce()).Then(
   //mutexMock.UnlockMock.CalledOnce());
}

RUN_TESTS(Tests)

int main(int argc, char* argv[])
{
   ZenUnitSelfTestMode::value = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
