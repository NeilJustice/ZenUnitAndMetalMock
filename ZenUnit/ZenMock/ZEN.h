#pragma once

#define ZEN(ZenMockAssertion) \
try \
{ \
   ZenMockAssertion; \
} \
catch (const ZenUnit::Anomaly& zenWrappedAnomaly) \
{ \
   throw ZenUnit::Anomaly::ZENWrapped( \
      "ZEN("#ZenMockAssertion")", zenWrappedAnomaly, FILELINE); \
}
