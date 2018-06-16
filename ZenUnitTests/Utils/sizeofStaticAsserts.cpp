#include "pch.h"

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(FileLine) == 16);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(FileLine) == 16);
#elif NDEBUG
static_assert(sizeof(FileLine) == 16);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(RunFilter) == 80);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(RunFilter) == 96);
#elif NDEBUG
static_assert(sizeof(RunFilter) == 80);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(ZenUnitArgs) == 88);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(ZenUnitArgs) == 104);
#elif NDEBUG
static_assert(sizeof(ZenUnitArgs) == 88);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(Anomaly) == 184);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(Anomaly) == 240);
#elif NDEBUG
static_assert(sizeof(Anomaly) == 200);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(AnomalyOrException) == 40);
#elif defined(_WIN64)
#if defined _DEBUG
//static_assert(sizeof(AnomalyOrException) == 40);
#elif NDEBUG
static_assert(sizeof(AnomalyOrException) == 40);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(FullTestName) == 24);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(FullTestName) == 24);
#elif NDEBUG
static_assert(sizeof(FullTestName) == 24);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(CallResult) == 24);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(CallResult) == 24);
#elif NDEBUG
static_assert(sizeof(CallResult) == 24);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(TestResult) == 240);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(TestResult) == 240);
#elif NDEBUG
static_assert(sizeof(TestResult) == 240);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(TestClassResult) == 96);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(TestClassResult) == 104);
#elif NDEBUG
static_assert(sizeof(TestClassResult) == 96);
#endif
#endif

#if defined __linux__ || defined __APPLE__
//static_assert(sizeof(Test) == 64);
#elif defined(_WIN64)
#if defined _DEBUG
static_assert(sizeof(Test) == 64);
#elif NDEBUG
static_assert(sizeof(Test) == 64);
#endif
#endif
