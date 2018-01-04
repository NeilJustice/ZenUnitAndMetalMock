#pragma once

template<typename T, typename ClassType, typename FunctionType, typename ExtraArgType>
struct ExtraArgMemberForEacherMock : public Zen::Mock<ExtraArgMemberForEacher<T, ClassType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID4_CONST(ExtraArgMemberForEach, vector<T>*, ClassType*, FunctionType, ExtraArgType)
   ZENMOCK_VOID5_CONST(RandomExtraArgMemberForEach, vector<T>*, ClassType*, FunctionType, ExtraArgType, unsigned)
};
