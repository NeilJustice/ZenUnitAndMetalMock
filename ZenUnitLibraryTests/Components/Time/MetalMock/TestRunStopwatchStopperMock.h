#pragma once

class TestRunStopwatchStopperMock : public Metal::Mock<TestRunStopwatchStopper>
{
public:
	METALMOCK_NONVOID1_CONST(string, StopTestRunStopwatchAndGetElapsedSeconds, ZenUnitTestRunner*)
};
