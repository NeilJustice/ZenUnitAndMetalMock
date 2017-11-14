#pragma once

#define ZEN(ZenMockAssertStatement) \
try \
{ \
   ZenMockAssertStatement; \
} \
catch (const ZenUnit::Anomaly& zenWrappedAnomaly) \
{ \
   throw ZenUnit::Anomaly::ZENWrapped( \
      "ZEN("#ZenMockAssertStatement")", zenWrappedAnomaly, FILELINE); \
}
