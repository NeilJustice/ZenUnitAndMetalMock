#pragma once

template<typename T, typename ClassType, typename FunctionType, typename Arg2Type>
class TwoArgMemberForEacherMock : public Metal::Mock<TwoArgMemberForEacher<T, ClassType, FunctionType, Arg2Type>>
{
public:
   METALMOCK_VOID4_CONST(TwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, const Arg2Type&)
   METALMOCK_VOID5_CONST(RandomTwoArgMemberForEach, vector<T>*, ClassType*, FunctionType, const Arg2Type&, unsigned)
};
