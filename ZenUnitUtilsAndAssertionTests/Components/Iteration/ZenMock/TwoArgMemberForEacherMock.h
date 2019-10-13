#pragma once

template<typename T, typename ClassType, typename FunctionType, typename Arg2Type>
class TwoArgMemberForEacherMock : public Zen::Mock<TwoArgMemberForEacher<T, ClassType, FunctionType, Arg2Type>>
{
public:
   ZENMOCK_VOID4_CONST(TwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, const Arg2Type&)
   ZENMOCK_VOID5_CONST(RandomTwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, const Arg2Type&, unsigned)
};
