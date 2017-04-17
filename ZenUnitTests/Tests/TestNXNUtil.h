#pragma once

template<typename TestNXNType>
void AssertTestNXNState(const TestNXNType& testNXN, size_t expectedNumberOfTestCases)
{
   ARE_EQUAL("TestName", testNXN.Name());
   ARE_EQUAL("TESTS(TestClassName)\nTEST(TestName)", testNXN.TestsAndTestLines());
   ARE_EQUAL("(0)", testNXN.FileLineString());
   ARE_EQUAL(expectedNumberOfTestCases, testNXN.NumberOfTestCases());
}
