#pragma once

template<typename T, typename ClassType, typename FunctionType, typename Arg2Type>
struct TwoArgMemberForEacherMock : public Zen::Mock<TwoArgMemberForEacher<T, ClassType, FunctionType, Arg2Type>>
{
   ZENMOCK_VOID4_CONST(TwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, Arg2Type)
   ZENMOCK_VOID5_CONST(RandomTwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, Arg2Type, unsigned)
};
