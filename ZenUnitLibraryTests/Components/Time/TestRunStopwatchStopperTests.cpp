#include "pch.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/ZenUnitTestRunnerMock.h"

TESTS(TestRunStopwatchStopperTests)
AFACT(StopTestRunStopwatchAndGetElapsedSeconds_ReturnsResultOfCallingZenUnitTestRunnerStopTestRunStopwatchAndGetElapsedSeconds)
EVIDENCE

TestRunStopwatchStopper _testRunStopwatchStopper;

TEST(StopTestRunStopwatchAndGetElapsedSeconds_ReturnsResultOfCallingZenUnitTestRunnerStopTestRunStopwatchAndGetElapsedSeconds)
{
   ZenUnitTestRunnerMock zenUnitTestRunnerMock;
   const string testRunDurationInSeconds = zenUnitTestRunnerMock.StopTestRunStopwatchAndGetElapsedSecondsMock.ReturnRandom();
   //
   const string returnedTestRunDurationInSeconds = _testRunStopwatchStopper.StopTestRunStopwatchAndGetElapsedSeconds(&zenUnitTestRunnerMock);
   //
   METALMOCK(zenUnitTestRunnerMock.StopTestRunStopwatchAndGetElapsedSecondsMock.CalledOnce());
   ARE_EQUAL(testRunDurationInSeconds, returnedTestRunDurationInSeconds);
}

RUN_TESTS(TestRunStopwatchStopperTests)
