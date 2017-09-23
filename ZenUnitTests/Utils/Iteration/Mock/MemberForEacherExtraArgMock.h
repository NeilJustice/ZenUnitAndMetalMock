#pragma once

template<typename T, typename ClassType, typename FunctionType, typename ExtraArgType>
struct MemberForEacherExtraArgMock : public Zen::Mock<MemberForEacherExtraArg<T, ClassType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID4_CONST(ForEach, const vector<T>*, const ClassType*, FunctionType, ExtraArgType)
   ZENMOCK_VOID5_CONST(RandomForEach, vector<T>*, const ClassType*, FunctionType, ExtraArgType, unsigned)
};
