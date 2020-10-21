#pragma once

struct IntializerConstructable
{
   int value;
   friend bool operator==(const IntializerConstructable& lhs, const IntializerConstructable& rhs);
   friend ostream& operator<<(ostream& os, const IntializerConstructable& intializerConstructable);
};
