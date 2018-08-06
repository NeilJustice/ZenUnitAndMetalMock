#include "pch.h"
#include "TestingTestClass.h"

bool TestingTestClass::s_destructorCalled;
template<> bool TestClass<TestingTestClass>::s_allNXNTestsRegistered;