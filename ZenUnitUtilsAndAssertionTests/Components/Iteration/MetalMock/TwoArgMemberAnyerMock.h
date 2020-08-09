#pragma once

template<typename CollectionType, typename ClassType, typename MemberPredicateType, typename Arg2Type>
class TwoArgMemberAnyerMock : public Zen::Mock<TwoArgMemberAnyer<CollectionType, ClassType, MemberPredicateType, Arg2Type>>
{
public:
   METALMOCK_NONVOID4_CONST(bool, TwoArgAny, const CollectionType&, const ClassType*, MemberPredicateType, Arg2Type)
};
