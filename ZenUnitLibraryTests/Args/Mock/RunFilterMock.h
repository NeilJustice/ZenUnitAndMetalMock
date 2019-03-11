#pragma once

class RunFilterMock : public Zen::Mock<RunFilter>
{
public:
	ZENMOCK_NONVOID1_CONST(bool, MatchesTestName, std::string_view)
	ZENMOCK_NONVOID1_CONST(bool, MatchesTestClassName, std::string_view)
	ZENMOCK_NONVOID3_CONST(bool, MatchesTestCase, std::string_view, std::string_view, size_t)
};
