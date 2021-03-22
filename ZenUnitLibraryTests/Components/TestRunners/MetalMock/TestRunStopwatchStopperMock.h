#pragma once

class TestRunStopwatchStopperMock : public Metal::Mock<TestRunStopwatchStopper>
{
public:
	METALMOCK_NONVOID0_CONST(string, StopTestRunStopwatchAndGetElapsedSeconds)
};
