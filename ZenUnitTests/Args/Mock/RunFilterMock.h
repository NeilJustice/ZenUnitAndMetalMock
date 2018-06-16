#pragma once

struct RunFilterMock : public Zen::Mock<RunFilter>
{
   ZENMOCK_NONVOID1_CONST(bool, MatchesTestName, const char*)
   ZENMOCK_NONVOID1_CONST(bool, MatchesTestClassName, const char*)
   ZENMOCK_NONVOID3_CONST(bool, MatchesTestCase, const char*, const char*, size_t)
};
